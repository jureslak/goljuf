<h3>Directory: '{{dir}}'</h3>

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
          {{!"{0:.2f}<br><span class='absolute'>({0:.2f})</span>".format(matrix[i][j])}}
        </td>
%     end
%   end
    </tr>
% end
  </tbody>
</table>
</div>
% if sumljivi:
  <h3>Sumljivi:</h3>
  <ul>
% for a, b, score in sumljivi:
  <li>
    <span class="file fileleft">{{a}}</span> :
    <span class="file fileright">{{b}}</span> ~
    <span class="score">{{score}}</span>
  </li>
% end
  </ul>
% else:
  <h3>Vse izgleda v redu!</h3>
% end
<hr>
