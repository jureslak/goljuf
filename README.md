# Goljuf
A program with web UI to mass compare files in specified folders, with main purpose to compare exams
for similarity. It calculates edit distance between a pair of every two files in each folder,
ignoring whitespace. The similarity is estimated based on relative edit distance: that is edit
distance, divided by the length of the longer of both files.

## Installation
If you have `g++` and `python3` installed, there is nothing for you to do here.
Otherwise you need to compile `edit_distance.cpp` into an executable however you like
and you're all set!

## Usage

Just run the Python script and specily a list of folders. Some test folders are provided.
All files directly within each of those folders will be compared. The output will be printed to the
standard output.

_Really_ basic usage:
```bash
$ python goljuf.py test
```
This compares all files directly in `test` directory and prints HTML to the standard output.

A more useful example:
```bash
$ python goljuf.py -r -f out.html test test2
```
This compares all files (including subfolders) within `test` to each other, and all files within
`test2` to each other, saving output to `out.html`. Naturally, one could also redirect the output to
file using `>` instead of a `-f` flag.

If the c++ executable is not found, the script will try to compile the cpp source file. Once that is
done, it will use the executable to compare the files and print the HTML page to the standard
output. See below for more details.

When the output file is produced you can open it in your favourite browser.

General form:
```
python goljuf.py [-h] [-e EXT [EXT ...]] [-r] [-t TRESHOLD] [-f OUTPUT_FILE]
                 [-x EXECUTABLE]
                 DIR [DIR ...]
```

### Options

* **`-e, --extensions`** Specify list of allowed exceptions. Only files with this extension will be
  compared. Default: `['c', 'cpp']`.
* **`-r, --recursive`** If this option is present, each directory is searched exhaustively. Default:
  off.
* **`-t, --treshold`** Specify a treshold, all files with relative difference less of equal than this
  are treated as suspicious. Default: `0.1`.
* **`-f, --output_file`** The output is printed to this file instead. Default: `stdout`.
* **`-x, --executable`** Specify a path to your compiled executable. Default: `edit_distance`.

For a complete option set, run

```bash
$ python goljuf.py -h

```

## UI
The web UI has some fancy features:
* hide all-green rows (non suspicious people)
* hide the tables (they can be quite big)
* sortable tables (click on headers)
* direct diff view (click on a cell, or `diff` link)
* useful tooltips and highlighting

## Further work
There is room for improvement in faster edit distance algorithms using Levenshtein automata.
The UI could see some design improvements as well.

Jure Slak
