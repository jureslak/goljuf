var files = {}; // for saving files, used in the dist_matrix.tpl

function all_green(table_id, idx) {
    var vrsta = $(table_id + ' tr')[idx];
    var cool = true;
    $(vrsta).find('td').each(function() {
        if (!$(this).hasClass("A") && !$(this).hasClass('empty')) {
            cool = false;
        }
    });
    return cool;
}


function hide_green(dir) {
    var table_id = '#table-'+dir;
    var trs = $(table_id + ' tr');
    for (var i = 1; i < trs.length; i++) {
        if (all_green(table_id, i, true)) {
            $(trs[i]).hide();
            $(trs).each(function() { $($(this).children()[i]).hide(); });
//             $(trs[i]).slideUp();
//             $(trs).each(function() { $($(this).children()[i]).slideUp(); });
        }
    }
    $("#clean-table-"+dir).hide();
    $("#unclean-table-"+dir).show();
}

function show_green(dir) {
    var table_id = '#table-'+dir;
    $(table_id + ' tr').each(function() { $(this).show(); });
    $(table_id + ' tr td').each(function() { $(this).show(); });
    $(table_id + ' tr th').each(function() { $(this).show(); });
    $("#clean-table-"+dir).show();
    $("#unclean-table-"+dir).hide();
}

$(document).on('keydown', function(e) {
    if (e.keyCode === 27) {  // ESC
        hide_overlay();
    }
});

function toggle_table(dir) {
    var table_id = '#table-div-'+dir;
    var button_id = '#toggle-table-'+dir;
    if ($(table_id).is(":hidden")) {
        $(table_id).show();
        $(button_id).html("Skrij tabelo");
    } else {
        $(table_id).hide();
        $(button_id).html("Pokaži tabelo");
    }
}

function diffUsingJS(s1, s2, name1, name2) {
    // get the baseText and newText values from the two textboxes, and split them into lines
    var base = difflib.stringAsLines(s1);
    var newtxt = difflib.stringAsLines(s2);

    // create a SequenceMatcher instance that diffs the two sets of lines
    var sm = new difflib.SequenceMatcher(base, newtxt);

    // get the opcodes from the SequenceMatcher instance
    // opcodes is a list of 3-tuples describing what changes should be made to the base text
    // in order to yield the new text
    var opcodes = sm.get_opcodes();
    var diffoutputdiv = document.getElementById("diffoutput");
    while (diffoutputdiv.firstChild) diffoutputdiv.removeChild(diffoutputdiv.firstChild);
    var contextSize = null;

    // build the diff view and add it to the current DOM
    diffoutputdiv.appendChild(diffview.buildView({
        baseTextLines: base,
        newTextLines: newtxt,
        opcodes: opcodes,
        // set the display titles for each resource
        baseTextName: name1,
        newTextName: name2,
        contextSize: contextSize,
        viewType: $("inline").checked ? 1 : 0
    }));

    $("#overlay").fadeIn();
    $("#diff_window").fadeIn();

    // scroll down to the diff view window.
//     location = url + "#diff";
}

function hide_overlay() {
  $("#diff_window").fadeOut();
  $("#overlay").fadeOut();
}

$(document).ready(function() {
    // distance table stuff
    $("table.dist-matrix").delegate('td:not(.empty)','mouseover mouseleave', function(e) {
        var idx = $(this).index();
        var td0 = $(this).parent().children()[0];
        var tr0 = $(this).parent().parent().parent().find("tr")[0]; // up to <table>, because we have tbody
        var div = $($(tr0).children()[idx]).find("div")[0];

        if (e.type == 'mouseover') {
            $(td0).addClass("hover");
            $(div).addClass("hover");
        } else {
            $(td0).removeClass("hover");
            $(div).removeClass("hover");
        }
    });

    // suspicious table stuff
    $(".suspicious").each(function() { $(this).tablesorter([4,0]); });

});
