<!DOCTYPE html>
<html>
  <head>
    <title>Goljuf 2.0</title>
    <link href="skin/bootstrap/css/bootstrap.min.css" type="text/css" rel="stylesheet">
    <link href="skin/bootstrap/css/bootstrap-theme.min.css" type="text/css" rel="stylesheet">
    <link href="skin/diffview.css" type="text/css" rel="stylesheet">
    <link rel='stylesheet' type='text/css' href='skin/style.css'>
    <meta charset='utf-8'>
    <meta name="author" content="Goljuf 2.0">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <script src="skin/jquery-2.1.3.min.js"></script>
    <script src="skin/jquery.tablesorter.min.js"></script>
    <script src="skin/bootstrap/js/bootstrap.min.js"></script>
    <script src="skin/difflib.js"></script>
    <script src="skin/diffview.js"></script>
    <script src="skin/script.js"></script>
  </head>
  <body>
    <div class='container-fluid main'>
      <h2>Rezultati primerjav</h2>
%    for dir in sorted(goljuf_data):
       {{!goljuf_data[dir].html}}
%    end
    <div id="diffoutput">
    </div>
    <footer>
      Goljuf 2.0, program za iskanje goljufov &ndash; ljudi s <i>preveč</i> podobnimi testi.
    </footer>
    </div>
  </body>
</html>
