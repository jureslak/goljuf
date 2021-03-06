<h3>Directory: '<span class="file">{{dir}}</span>'</h3>

<script>
% for ime, contents in zip(file_list, file_contents):
  files[{{!repr(ime)}}] = {{!repr(contents)}};
% end
</script>

<a class="btn btn-default showhide" id="toggle-table-{{dir_id}}"
   onclick="toggle_table('{{dir_id}}')">Skrij tabelo</a>
<a class="btn btn-default showhide" id="clean-table-{{dir_id}}"
   onclick="hide_green('{{dir_id}}')">Skrij zelene</a>
<a class="btn btn-default showhide" id="unclean-table-{{dir_id}}"
   onclick="show_green('{{dir_id}}')" style="display: none">Pokaži zelene</a>
<div id='table-div-{{dir_id}}' class="tablediv">
<table id='table-{{dir_id}}' class='dist-matrix table-header-rotated'>
  <thead><tr>
    <th class='first'></th>
% for i in range(len(matrix)):
      <th class='rotate'><div><span>
        <a class="file" href="{{file_list[i]}}">{{display_file_list[i]}}</a>
      </span></div></th>
% end
  </tr></thead>
  <tbody>
% for i in range(len(matrix)):
  <tr><th class='levo'>
      <a class="file" href="{{file_list[i]}}">{{display_file_list[i]}}</a>
    </th>
%   for j in range(len(matrix[i])):
%     if i == j:
        <td class='empty'></td>
%     else:
%       a = file_list[i]; b = file_list[j];
%       cls = class_picker(matrix[i][j])
%       title = "({}, {})".format(display_file_list[i], display_file_list[j])
        <td class="{{cls}} data" title="{{title}}"
            onclick="diffUsingJS(files[{{repr(a)}}], files[{{repr(b)}}], {{repr(a)}}, {{repr(b)}});">
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
<h3>Sumljivi (rel &#8804; {{threshold}}):</h3>
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
%     a = display_file_list[i]; b = display_file_list[j];
      <tr>
        <td class="fileleft"><a class="file" href="{{dir}}/{{a}}">{{a}}</a></td>
        <td class="fileright"><a class="file" href="{{dir}}/{{b}}">{{b}}</a></td>
        <td class="abs-score">{{score[0]}}</td>
        <td class="rel-score">{{"{:.4f}".format(score[1])}}</td>
        <td class="diff"><a class="diff"
            onclick="diffUsingJS(files[{{repr(a)}}], files[{{repr(b)}}], {{repr(a)}}, {{repr(b)}});">
            diff</a></td>
      </tr>
%   end
    </tbody>
  </table>
% else:
  <h3>Vse izgleda v redu!</h3>
% end
<hr>
