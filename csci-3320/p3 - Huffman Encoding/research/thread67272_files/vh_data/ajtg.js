if (typeof(aj_server) != 'undefined' && typeof(aj_adspot) != 'undefined' && typeof(aj_page) != 'undefined' && typeof(aj_zone) != 'undefined') {
    aj_tag = aj_server;
	aj_tag += aj_adspot+"/"+aj_page+"/vj?z="+aj_zone;

	if (typeof(aj_ch) != 'undefined' && aj_ch != "") {
		aj_tag += "&ch="+aj_ch;
	}
	if (typeof(aj_dim) != 'undefined' && aj_dim != "") {
		aj_tag += "&dim="+aj_dim;
	}   	
	if (typeof(aj_ct) != 'undefined' && aj_ct != "") {
		aj_tag += "&ct="+aj_ct;
	}
	if (typeof(aj_pos) == 'undefined') {
	    aj_pos = 1;
	} else {
		aj_pos++;
	}
	aj_tag += "&pos="+aj_pos;

	if (typeof(aj_kw) != 'undefined' && aj_kw != "") {
		aj_tag += "&kw="+aj_kw;
	}

	if (typeof(aj_pv) != 'undefined' && aj_pv == true) {
		if (typeof(aj_pv_rnd) == 'undefined') {
			aj_pv_rnd = Math.round( (Math.random() + "") * 10000000000000000 ) + 1;
		}
		aj_tag += "&pv=" + aj_pv_rnd;
	}

	aj_tag += "&nc=" + Math.round( (Math.random() + "") * 100000000 ) + 1;

	if (typeof(aj_click) != 'undefined' && aj_click != "") {
		aj_tag += "&click="+escape(aj_click);		
	}

	document.write('<'+'scr'+'ipt type="text/javas'+'cript" language="JavaScript" src="'+aj_tag+'"></'+'scr'+'ipt>');
}
