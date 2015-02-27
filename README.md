# Goljuf
A program with web UI to mass compare files in specified folders, with main purpose to compare exams
for similarity. It calculates edit distance between a pair of every two files in each folder,
ignoring whitespace. The similarity is estimated based on relative edit distance: that is edit
distance, divided by the length of the longer of both files.

## Installation
You need to compile `edit_distance.cpp` and you're all set! Naturally, you also need to have Python
3 installed.

## Usage

Just run the Python script and specily a list of folders. All files directly within each of those
folders will be compared. The output will be printed to the standard output.

```bash
$ python goljuf.py test
```

A more useful demo:

```bash
$ python goljuf.py -r test test2 > out.html
```

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
