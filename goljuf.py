import argparse
import bottle
import os
import subprocess
import sys

def dir_type(dirname):
    if not os.path.isdir(dirname):
        raise argparse.ArgumentTypeError("'{}' is not a valid directory!".format(dirname))
    return dirname.rstrip('/')

parser = argparse.ArgumentParser(description=(
    "Compare files within specified directories for similarity."))
parser.add_argument('directories', metavar='DIR', type=dir_type, nargs='+', help=(
    "directory containing files to be compared to each other."))
parser.add_argument('-e', '--extensions', metavar='EXT', nargs='+',
    default=['c', 'cpp'], help=("only files with specified extensions are compared."))
parser.add_argument('-r', '--recursive', default=False, action='store_true', help=(
    "compare ALL the files in the specified directories, including files from subdirectories"))
parser.add_argument('-t', '--treshold', default=0.2, action='store', type=float, help=(
    "print files with relative distance below this as suspicious"))
parser.add_argument('-f', '--output_file', default=sys.stdout, action='store',
    type=argparse.FileType('w'), help=("path to the file for saving html output, eg. ../ui/display.html"))
parser.add_argument('-x', '--executable', default='edit_distance', action='store', help=(
    "path to the executable, eg. ../bin/calc_distance"))

class Goljuf(object):

    @staticmethod
    def kriterij(value):
        value = value[1]
        if value >= 0.4: return "A"
        if value >= 0.3: return "B"
        if value >= 0.2: return "C"
        if value >= 0.1: return "D"
        return "E"

    def __init__(self, directory, options):
        self.recursive = bool(options.recursive)
        self.directory = directory
        self.valid_extensions = list(options.extensions)
        self.treshold = float(options.treshold)
        self.executable = options.executable;

    def has_valid_extension(self, filename):
        for ext in self.valid_extensions:
            if filename.endswith('.'+ext):
                return True
        return False

    def make_file_list(self):
        if not self.recursive:
            self.file_list = [os.path.join(self.directory, filename) for filename in os.listdir(self.directory)]
            self.file_list = list(filter(os.path.isfile, self.file_list))
        else:
            self.file_list = []
            for dirpath, dirs, files in os.walk(self.directory):
                self.file_list.extend([os.path.join(dirpath, filename) for filename in files])

        size = len(self.file_list)
        self.file_list = [name for name in self.file_list if os.stat(name).st_size > 0]
        empty = size - len(self.file_list)
        if empty:
            print("[note]", "Ignoring {} empty files.".format(empty))
        self.file_list = sorted(filter(self.has_valid_extension, self.file_list))
        self.file_contents_list = []
        for x in self.file_list:
            try:
                self.file_contents_list.append(open(x, 'r', encoding='utf-8').read())
            except UnicodeDecodeError:
                self.file_contents_list.append(open(x, 'r', encoding='windows-1250').read())
        return self.file_list

    def compare_files(self):
        file_list = self.file_list
#          print(' '.join(['./edit_distance'] + file_list))
        proc = subprocess.Popen(['./' + self.executable] + file_list, stdout=subprocess.PIPE);
        stdout, stderr = proc.communicate()
        if stderr is not None:
            raise "Subproccess returned errors: " + stderr

        distances = stdout.decode().split()
        for i in range(len(distances)):
            s = distances[i].split("~")
            distances[i] = (int(s[0]), float(s[1]))

        n = len(file_list)
        dist_matrix = [[0] * n for i in range(n)]

        j = 0
        k = 1
        for i, dist in enumerate(distances):
            if k == n:
                j += 1
                k = j + 1
            dist_matrix[j][k] = dist
            dist_matrix[k][j] = dist
            k += 1

        self.dist_matrix = dist_matrix
        return dist_matrix

    def extract_suspicious(self):
        self.suspicious = []
        for i in range(len(self.dist_matrix)):
            for j in range(i+1, len(self.dist_matrix)):
                if self.dist_matrix[i][j][1] < self.treshold:
                    self.suspicious.append((i, j, self.dist_matrix[i][j]))
        self.suspicious.sort(key=lambda x:x[2])

    def __str__(self):
        r = ""
        for i, f in zip(self.dist_matrix, self.file_list):
            r += "{: <35}".format(f)
            for j in i:
                r += "{: >2.2f}  ".format(j)
            r += '\n'
        return r

    def investigate(self):
        self.make_file_list()
        self.compare_files()
        self.extract_suspicious()


class HtmlPrinter(object):
    def __init__(self, goljuf_data):
        self.goljuf_data = goljuf_data

    def filename_strip(self):
        for dir in self.goljuf_data:
            goljuf = self.goljuf_data[dir]
            goljuf.display_file_list = []
            for file in goljuf.file_list:
                goljuf.display_file_list.append(file[len(dir)+1:])

    def generate_goljuf_html(self):
        self.filename_strip()
        for i, dir in enumerate(self.goljuf_data):
            goljuf = self.goljuf_data[dir]
            goljuf.html = bottle.template('skin/dist_matrix', {
                'matrix': goljuf.dist_matrix,
                'file_list': goljuf.display_file_list,
                'class_picker': Goljuf.kriterij,
                'dir': dir,
                'dir_id': 'dirname{}'.format(i),
                'sumljivi': goljuf.suspicious,
                'treshold': goljuf.treshold,
                'file_contents': goljuf.file_contents_list})

    def html(self):
        self.generate_goljuf_html()
        return bottle.template('skin/main', {'goljuf_data': self.goljuf_data})

args = parser.parse_args()

if not os.path.isfile(args.executable):
    val = subprocess.call(['g++', '-o', 'edit_distance', '-O3', '--std=c++11', 'edit_distance.cpp'])
    if val == 0:
        args.executable = 'edit_distance'
    else:
        raise OSError("Executable {} not found! Also failed to compile a new one.".format(args.executable))

G = {}
for directory in args.directories:
    g = Goljuf(directory, args)
    g.investigate()
    G[directory] = g

printer = HtmlPrinter(G)
print(printer.html(), file=args.output_file)
print("Saved report to {}.".format(args.output_file.name))
