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
$(document).ready(function() {
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
});
