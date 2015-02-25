<h3>Directory: '<span class="file">{{dir}}</span>'</h3>

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
%       cls = class_picker(matrix[i][j])
%       title = "({}, {})".format(file_list[i], file_list[j])
        <td class="{{cls}}" title="{{title}}">
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
% st = " title='Click to sort.'"
      <th{{!st}}>File 1</th>
      <th{{!st}}>File 2</th>
      <th{{!st}}>Abs. score</th>
      <th{{!st}}>Rel. score</th>
      <th{{!st}}>View diff</th>
    </thead>
    <tbody>
%   for a, b, score in sumljivi:
      <tr>
        <td><span class="file fileleft">{{a}}</span></td>
        <td><span class="file fileright">{{b}}</span></td>
        <td><span class="abs-score">{{score[0]}}</span></td>
        <td><span class="rel-score">{{"{:.4f}".format(score[1])}}</span></td>
        <td><span class="diff">diff</span></td>
      </tr>
%   end
    </tbody>
  </table>
% else:
  <h3>Vse izgleda v redu!</h3>
% end
<hr>
