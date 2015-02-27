<h3>Directory: '<span class="file">{{dir}}</span>'</h3>

<script>
% for ime, contents in zip(file_list, file_contents):
  files[{{!repr(ime)}}] = {{!repr(contents)}};
% end
</script>

<a class="btn btn-default showhide" id="toggle-table-{{dir}}"
   onclick="toggle_table('{{dir}}')">Skrij tabelo</a>
<a class="btn btn-default showhide" id="clean-table-{{dir}}"
   onclick="hide_green('{{dir}}')">Skrij zelene</a>
<a class="btn btn-default showhide" id="unclean-table-{{dir}}"
   onclick="show_green('{{dir}}')" style="display: none">Pokaži zelene</a>
<div id='table-div-{{dir}}' class="tablediv">
<table id='table-{{dir}}' class='dist-matrix table-header-rotated'>
  <thead><tr>
    <th class='first'></th>
% for i in range(len(matrix)):
      <th class='rotate'><div><span>
        <a class="file" href="{{dir}}/{{file_list[i]}}">{{file_list[i]}}</a>
      </span></div></th>
% end
  </tr></thead>
  <tbody>
% for i in range(len(matrix)):
  <tr><th class='levo'>
      <a class="file" href="{{dir}}/{{file_list[i]}}">{{file_list[i]}}</a>
    </th>
%   for j in range(len(matrix[i])):
%     if i == j:
        <td class='empty'></td>
%     else:
%       a = file_list[i]; b = file_list[j];
%       cls = class_picker(matrix[i][j])
%       title = "({}, {})".format(file_list[i], file_list[j])
        <td class="{{cls}} data" title="{{title}}"
            onclick="diffUsingJS(files[{{repr(a)}}], files[{{repr(b)}}]);">
          {{!"{0[1]:.2f}<br><span class='absolute'>({0[0]})</span>".format(matrix[i][j])}}
        </td>
%     end
%   end
    </tr>
% end
  </tbody>
</table>
</div>
% if sumljivi:
<h3>Sumljivi (rel &#8804; {{treshold}}):</h3>
  <table class="suspicious tablesorter">
    <thead>
      <tr>
% st = " title='Click to sort.'"
        <th{{!st}}>File 1</th>
        <th{{!st}}>File 2</th>
        <th{{!st}}>Abs. score</th>
        <th{{!st}}>Rel. score</th>
        <th{{!st}}>View diff</th>
      </tr>
    </thead>
    <tbody>
%   for i, j, score in sumljivi:
%     a = file_list[i]; b = file_list[j];
      <tr>
        <td class="fileleft"><a class="file" href="{{a}}">{{a}}</a></td>
        <td class="fileright"><a class="file" href="{{b}}">{{b}}</a></td>
        <td class="abs-score">{{score[0]}}</td>
        <td class="rel-score">{{"{:.4f}".format(score[1])}}</td>
        <td class="diff"><a class="diff"
            onclick="diffUsingJS(files[{{repr(a)}}], files[{{repr(b)}}]);">
            diff</a></td>
      </tr>
%   end
    </tbody>
  </table>
% else:
  <h3>Vse izgleda v redu!</h3>
% end
<hr>
