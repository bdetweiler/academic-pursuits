<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd"><html><head>


<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"><title>Input/Output with files</title>

<link rel="shortcut icon" href="http://www.cplusplus.com/favicon.ico">
<style type="text/css">
<!--
BODY, TABLE, INPUT, SELECT, TEXTAREA {font-family:verdana,arial,helvetica,sans-serif; font-size:12px; color:black}
BODY, FORM, PRE {margin:0; padding:0}
DT {font-weight:bold} DD, UL {margin-bottom:12px} UL {margin-top:4px} LI {margin-bottom:4px}
A:link, A:visited, A:active {text-decoration: none; color:#000070} A:hover {text-decoration: underline; color:#0000A0}

.imgbox {line-height:1px;} /* for FF */

.bar {color:white; background:url("/img/headbg.gif"); line-height:20px; vertical-align:top}
.bar TABLE {color:white;font-size:9px; line-height:16px;}
.bar A:link, .bar A:visited, .bar A:active {color:white} .bar A:hover {text-decoration:none; color:yellow}
.bar .txt {height:14px; background-color:#C0C0FF; border: 1px inset}
.bar .btn {height:18px; background-color:#C0C0FF; font-size:9px; border:1px outset}

.left {border-right:1px solid black}
.left TABLE {border:#00007F 1px solid; margin-top:5px; width:160px; background:white; border-collapse:collapse;}
.left TD {color:#000070; text-align:left;font-family:verdana,arial,helvetica,sans-serif; font-size:x-small;}
.left TH {height:14px; color:#FFFFFF; background:blue url("/img/blue.gif"); font-family:verdana,arial,helvetica,sans-serif; font-size:xx-small;}
.left TH A:link, .left TH A:visited, .left TH A:active {text-decoration: none;color:#FFFFFF;} .left TH A:hover {text-decoration: none;color:yellow}

.content {padding: 5px}
.list {width:98%} .list TD {border:silver 1px solid; position:relative; left:2%} .list .tit {width:160px}
.boxed {border-collapse: collapse;} .boxed TH {background:#E0E0E0; border:1px solid black;} .boxed TD {border:1px solid black}

.code {background:#EFEFFF; border: 1px solid #C0C0D0;}
.code A:link, .code A:visited, .code A:active {text-decoration: none; color:black} .code A:hover {text-decoration: none; color:black; background:yellow}
.codebox {width:100%;margin:0px; padding:0px; border:none}
.kw, A.kw:hover, A.kw:link, A.kw:visited, A.kw:active {color:#0000B0}
.prep {color:#500070} .comm {color:#007000} .str {color:#600030}

.snippet {margin-left:20px}
.result {width:50%; background:#E7E7E7; border: 1px solid #C0C0C0; vertical-align:top}

.warning {background:#FFC000;border:2px solid red}
.selected {background:#F0F0F0;}

.stdform, .stdform TH {border:#00007F 1px solid} .stdform TD {border:#707080 1px solid; text-align:left}
.stdform TH {color:#FFFFFF; background:blue url("/img/blue.gif"); } .stdform TH A:link, .stdform TH A:visited, .stdform TH A:active {color: white} .stdform TH A:hover {color:yellow}
.stdform TR TD {background: #F0F0FF} .stdform TR.odd TD {background: #E0E0FF}
.stdform TEXTAREA, .stdform .value {font-family:courier,monospace} .stdform .field {text-align:right;font-weight:bold} .stdform .description {font-size:80%;} .stdform .number {text-align:center}
.stdform .txt, .stdform SELECT, .stdform TEXTAREA {border:black 1px solid; background-color:#FFFFF0;} .stdform .buttons {text-align:center; padding:5px}
.stdform TR.separator TD {background: white; font-weight:bold }

.poff {background:#E0E0FF; margin-bottom:3px; border: 1px solid #A0A0C0; border-collapse:collapse;}
.pon {background:#D0D0FF; margin-bottom:3px; border: 1px solid #4040B0; border-collapse:collapse; cursor:pointer;}
.sep TD {font-size:small;} .sep TD A {text-decoration: none}
.mn TD {font-size:x-small; text-indent:10px;}
.bot TD {font-size:xx-small; color:#804000; background:#F0F0FF;margin:0px; padding:0px} .bot TD A {color:#804000}

.errors, .errors TH {border:#7F0000 1px solid;} .errors TH {color:#FFFFFF; background:red; } .errors TD {border:#807070 1px solid; background: #FFE0E0; text-align:left}

.list {width:98%}
	.list TD {border:silver 1px solid; position:relative; left:2%}
	.list TD IMG {padding-right:5px}
	.list TH {padding-top:5px; text-align:left}
-->
</style>

<script type="text/javascript">
<!--
function GetCookie(name) {
  var dc = document.cookie;
  var prefix = name + '=';
  var begin = dc.indexOf('; ' + prefix);
  if (begin == -1) {
    begin = dc.indexOf(prefix);
    if (begin != 0) return null;
  } else
    begin += 2;
  var end = document.cookie.indexOf(';', begin);
  if (end == -1)
    end = dc.length;
  var sret=unescape(dc.substring(begin + prefix.length, end));
  var aret=sret.split('+'); sret=aret.join(' ');
  return sret;
}

var user=GetCookie ('codehq_user');

var mo = new Array("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");

function When(ts) {
 var dt = new Date(ts*1000);
 document.write(mo[dt.getMonth()]+" "+dt.getDate()+", "+(dt.getYear()+(dt.getYear()<1900?1900:0)));
 document.write(" at "+((dt.getHours()%12)==0?12:dt.getHours()%12)+":"+(dt.getMinutes()<10?"0":"")+dt.getMinutes()+(dt.getHours()<12?"am":"pm"));
}

function LoginBox() {
if (!user)
{
	document.write ('<table cellspacing=2 cellpadding="0" valign="top">');
	document.write ('<tr><td align="right"><b>login:<\/b><\/td><td><input class="txt" name="l" size="4" type="text"><\/td><td><input class="txt" name="p" size="4" type="password"><\/td><td align="center"><input class="btn" value="sign in" type="submit"><\/td><\/tr>');
	document.write ('<tr><td colspan="3" align="right">remember me<input name="rememberme" value="1" type="checkbox" style="vertical-align:middle"><\/td>');
	document.write (' <td align="center">[<a href="/member/signup.form">register<\/a>]<\/td><\/tr>');
	document.write ('<\/table>');
}
else
{
	document.write ('<table width="150" cellspacing="2" cellpadding="0" valign="top">');
	document.write ('<tr><td colspan="2" align="center">Logged in as: <b>'+user+'<\/b><\/td><\/tr>');	
	document.write ('<tr><td align="right"><input class="btn" value="log out" type="submit"><input type="hidden" name="redirectto" value="/doc/tutorial/files.html"><input type="hidden" name="logout" value="sign out"><\/td>');
	document.write ('<td align="left">[<b><a href="/member/">profile<\/a><\/b>]');
	document.write ('<\/td><\/tr>');
	document.write ('<\/table>');
}
}

var lowuser; if (user) lowuser=user.toLowerCase();
var faaccess=new Boolean ( (( GetCookie('codehq_access') & 256 )==256 ));

function SuOptions() {
	if ((faaccess==true)||(lowuser=='juan soulie'))
	{
		document.write(' [<a href="/admin/publish.form?what=edit&itemid=24">Edit this document<\/a>] ');
	}	}
//-->
</script></head><body bgcolor="#d7d7d7">

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tbody><tr>
<td rowspan="2" class="imgbox" bgcolor="#b0c0d0" valign="top"><a href="http://www.cplusplus.com/"><img src="file_io_cplusplus_files/headlogo1.gif" alt="cplusplus.com" border="0" height="75" width="165"></a></td>
<td class="imgbox" bgcolor="#ffffff" valign="top"><a href="http://www.cplusplus.com/"><img src="file_io_cplusplus_files/headlogo2.gif" alt="cplusplus.com" border="0" height="18" width="33"></a></td>
<td bgcolor="#d7d7d7" width="95%"></td><td bgcolor="#d7d7d7"></td></tr>
<tr><td class="imgbox" bgcolor="#ffffff" valign="top"><a href="http://www.cplusplus.com/"><img src="file_io_cplusplus_files/headlogo3.gif" alt="cplusplus.com" border="0" height="57" width="33"></a></td>
<td class="bar" valign="top" width="95%">
   &nbsp; <b>
<a href="http://www.cplusplus.com/">C++</a> : <a href="http://www.cplusplus.com/doc/">Documentation</a> : <a href="http://www.cplusplus.com/doc/tutorial/">C++ Language Tutorial</a> : Input/Output with files  </b>
<br>
   <form name="search" action="/query/search.cgi" method="get">
   &nbsp; Search: <input name="q" size="13" class="txt"> <input value="Search" class="btn" type="submit">
   </form></td>



<td class="bar" valign="top">
<form name="login" action="/member/login.form" method="post"><input name="login" value="1" type="hidden"><input name="redirectto" value="/doc/tutorial/files.html" type="hidden">

<script type="text/javascript">
<!--
LoginBox();
// -->
</script><table valign="top" cellpadding="0" cellspacing="2"><tbody><tr><td align="right"><b>login:</b></td><td><input class="txt" name="l" size="4" type="text"></td><td><input class="txt" name="p" size="4" type="password"></td><td align="center"><input class="btn" value="sign in" type="submit"></td></tr><tr><td colspan="3" align="right">remember me<input name="rememberme" value="1" style="vertical-align: middle;" type="checkbox"></td> <td align="center">[<a href="http://www.cplusplus.com/member/signup.form">register</a>]</td></tr></tbody></table>
</form>
<noscript><center>javascript and cookies required</center></noscript>

</td></tr>

</tbody></table>

<table border="0" cellpadding="0" cellspacing="0" width="100%"><tbody><tr>
<td style="border-right: 1px solid black; line-height: 1px;" bgcolor="#b0c0d0" width="165"><img src="file_io_cplusplus_files/165x1.gif" alt="-" height="1" width="165"></td>
<td class="imgbox" bgcolor="white" width="99%"><img src="file_io_cplusplus_files/165x1.gif" alt="-" height="1" width="165"></td>
</tr>
<tr>


<!-- left -->
<td class="left" align="center" bgcolor="#b0c0d0" valign="top" width="165"><table class="box">
	<tbody><tr><th><a href="http://www.cplusplus.com/">C++</a></th></tr>
	<tr><td><a href="http://www.cplusplus.com/info/"><b>Information</b></a></td></tr>
	<tr><td><span class="selected"><a href="http://www.cplusplus.com/doc/"><b>Documentation</b></a></span></td></tr>
	<tr><td><a href="http://www.cplusplus.com/reference/"><b>Reference</b></a></td></tr>
	<tr><td><a href="http://www.cplusplus.com/articles/"><b>Articles</b></a></td></tr>
	<tr><td><a href="http://www.cplusplus.com/src/"><b>Sourcecode</b></a></td></tr>
	<tr><td><a href="http://www.cplusplus.com/forum/"><b>Forum</b></a></td></tr>
</tbody></table>
<table class="box">
	<tbody><tr><th><a href="http://www.cplusplus.com/doc/">Documentation</a></th></tr>
	<tr><td><span class="selected"><a href="http://www.cplusplus.com/doc/tutorial/"><b>C++ Language Tutorial</b></a></span></td></tr>
	<tr><td><a href="http://www.cplusplus.com/doc/ascii.html">Ascii Codes</a></td></tr>
	<tr><td><a href="http://www.cplusplus.com/doc/boolean.html">Boolean Operations</a></td></tr>
	<tr><td><a href="http://www.cplusplus.com/doc/hex.html">Numerical Bases</a></td></tr>
</tbody></table>
<table class="box">
	<tbody><tr><th><a href="http://www.cplusplus.com/doc/tutorial/">C++ Language Tutorial</a></th></tr>
	<tr><td><b>Introduction:</b></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/introduction.html">Instructions for use</a></td></tr>
	<tr><td><b>Basics of C++:</b></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/program_structure.html">Structure of a program</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/variables.html">Variables. Data Types.</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/constants.html">Constants</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/operators.html">Operators</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/basic_io.html">Basic Input/Output</a></td></tr>
	<tr><td><b>Control Structures:</b></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/control.html">Control Structures</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/functions.html">Functions (I)</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/functions2.html">Functions (II)</a></td></tr>
	<tr><td><b>Compound Data Types:</b></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/arrays.html">Arrays</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/ntcs.html">Character Sequences</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/pointers.html">Pointers</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/dynamic.html">Dynamic Memory</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/structures.html">Data Structures</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/other_data_types.html">Other Data Types</a></td></tr>
	<tr><td><b>Object Oriented Programming:</b></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/classes.html">Classes (I)</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/classes2.html">Classes (II)</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/inheritance.html">Friendship and inherita...</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/polymorphism.html">Polymorphism</a></td></tr>
	<tr><td><b>Advanced Concepts:</b></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/templates.html">Templates</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/namespaces.html">Namespaces</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/exceptions.html">Exceptions</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/typecasting.html">Type Casting</a></td></tr>
	<tr><td>· <a href="http://www.cplusplus.com/doc/tutorial/preprocessor.html">Preprocessor directives</a></td></tr>
	<tr><td><b>C++ Standard Library:</b></td></tr>
	<tr><td>· <span class="selected">Input/Output with files</span></td></tr>
</tbody></table>

<br>

<img src="file_io_cplusplus_files/165x1.gif" alt="-" height="1" width="165">
</td>
<!-- /left -->

<td bgcolor="white" valign="top" width="99%">
<div class="content">

<script type="text/javascript"><!--
google_ad_client = "pub-5777024789006368";
google_ad_width = 728;
google_ad_height = 90;
google_ad_format = "728x90_as";
google_ad_type = "text_image";
google_ad_channel = "4238618971";
google_color_border = ["FFFFFF","0066CC","CCCCCC","FFFFFF"];
google_color_bg = ["FFFFFF","FFFFFF","CCCCCC","FFFFFF"];
google_color_link = ["3333CC","000070","000000","2D6E89"];
google_color_text = ["000000","000000","333333","000000"];
google_color_url = ["000000","000070","666666","2D6E89"];
//--></script>
<script language="javascript" src="file_io_cplusplus_files/get.media"></script><iframe name="google_ads_frame" src="file_io_cplusplus_files/ads.htm" marginwidth="0" marginheight="0" vspace="0" hspace="0" allowtransparency="true" frameborder="0" height="90" scrolling="no" width="728"></iframe>
<noscript><a href="http://media.fastclick.net/w/click.here?sid=4636&m=1&c=1" target="_top">
<img src="http://media.fastclick.net/w/get.media?sid=4636&m=1&tp=5&d=s&c=1"
width=728 height=90 border=1></a></noscript><br><table width="100%"><tbody><tr><td><h1>Input/Output with files</h1></td>
<td align="right"><table><tbody><tr><td align="right">Published by <b><a href="http://www.cplusplus.com/member/Juan_Soulie/">Juan Soulie</a></b></td></tr>
<tr><td align="right"><small>Last update on <script type="text/javascript">When(1181860753)</script>Jun 15, 2007 at 2:39am</small></td></tr>
</tbody></table>
</td></tr></tbody></table>C++ provides the following classes to perform output and input of characters to/from files: <p></p><ul>
<li><b>ofstream:</b> Stream class to write on files</li>
<li><b>ifstream:</b> Stream class to read from files</li>
<li><b>fstream:</b> Stream class to both read and write from/to files.</li>
</ul><p>These classes are derived directly or indirectly from the classes <tt>istream</tt>, and <tt>ostream</tt>. We have already used objects whose types were these classes: <tt>cin</tt> is an object of class <tt>istream</tt> and <tt>cout</tt> is an object of class <tt>ostream</tt>.
Therfore, we have already been using classes that are related to our
file streams. And in fact, we can use our file streams the same way we
are already used to use <tt>cin</tt> and <tt>cout</tt>, with the only difference that we have to associate these streams with physical files. Let's see an example:</p><p></p><table class="codebox"><tbody><tr><td class="code"><pre><span class="comm">// basic file operations</span>
<span class="prep">#include &lt;iostream&gt;</span>
<span class="prep">#include &lt;fstream&gt;</span>
<span class="kw">using</span> <span class="kw">namespace</span> std;

<span class="kw">int</span> main () {
  ofstream myfile;
  myfile.open (<span class="str">"example.txt"</span>);
  myfile &lt;&lt; <span class="str">"Writing this to a file.\n"</span>;
  myfile.close();
  <span class="kw">return</span> 0;
}
</pre></td><td class="result"><pre>[file example.txt]
Writing this to a file
</pre></td></tr></tbody></table><p>This code creates a file called <tt>example.txt</tt> and inserts a sentence into it in the same way we are used to do with <tt>cout</tt>, but using the file stream <tt>myfile</tt> instead.</p><p>But let's go step by step:</p><p></p><h3>Open a file</h3><p>The
first operation generally performed on an object of one of these
classes is to associate it to a real file. This procedure is known as
to <i>open a file</i>. An open file is represented within a program by
a stream object (an instantiation of one of these classes, in the
previous example this was <tt>myfile</tt>) and any input or output operation performed on this stream object will be applied to the physical file associated to it.</p><p>In order to open a file with a stream object we use its member function <tt>open()</tt>:</p><p><tt>
open (filename, mode);<br></tt></p><p>Where <tt>filename</tt> is a null-terminated character sequence of type <tt>const char *</tt> (the same type that string literals have) representing the name of the file to be opened, and <tt>mode</tt> is an optional parameter with a combination of the following flags:</p><p></p><table class="boxed">
<tbody><tr><td>ios::in</td><td>Open for input operations.</td></tr>
<tr><td>ios::out</td><td>Open for output operations.</td></tr>
<tr><td>ios::binary</td><td>Open in binary mode.</td></tr>
<tr><td>ios::ate</td><td>Set the initial position at the end of the file.<br>If this flag is not set to any value, the initial position is the beginning of the file.</td></tr>
<tr><td>ios::app</td><td>All output operations are performed at the end
of the file, appending the content to the current content of the file.
This flag can only be used in streams open for output-only operations.</td></tr>
<tr><td>ios::trunc</td><td>If the file opened for output operations already existed before, its previous content is deleted and replaced by the new one.</td></tr>
</tbody></table><p>All these flags can be combined using the bitwise operator OR (<tt>|</tt>). For example, if we want to open the file <tt>example.bin</tt> in binary mode to add data we could do it by the following call to member function <tt>open()</tt>:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre>ofstream myfile;
myfile.open (<span class="str">"example.bin"</span>, ios::out | ios::app | ios::binary); 
</pre></td></tr></tbody></table><p>Each one of the <tt>open()</tt> member functions of the classes <tt>ofstream</tt>, <tt>ifstream</tt> and <tt>fstream</tt> has a default mode that is used if the file is opened without a second argument:</p><p></p><table class="boxed">
<tbody><tr><th>class</th><th>default mode parameter</th></tr>
<tr><td>ofstream</td><td>ios::out</td></tr>
<tr><td>ifstream</td><td>ios::in</td></tr>
<tr><td>fstream</td><td>ios::in | ios::out</td></tr>
</tbody></table><p>For <tt>ifstream</tt> and <tt>ofstream</tt> classes, <tt>ios::in</tt> and <tt>ios::out</tt> are automatically and respectivelly assumed, even if a mode that does not include them is passed as second argument to the <tt>open()</tt> member function.</p><p>The
default value is only applied if the function is called without
specifying any value for the mode parameter. If the function is called
with any value in that parameter the default mode is overridden, not
combined.</p><p>File streams opened in binary mode perform input and
output operations independently of any format considerations.
Non-binary files are known as <i>text files</i>, and some translations may occur due to formatting of some special characters (like newline and carriage return characters).</p><p>Since
the first task that is performed on a file stream object is generally
to open a file, these three classes include a constructor that
automatically calls the <tt>open()</tt> member function and has the exact same parameters as this member. Therefore, we could also have declared the previous <tt>myfile</tt> object and conducted the same opening operation in our previous example by writing:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre>ofstream myfile (<span class="str">"example.bin"</span>, ios::out | ios::app | ios::binary);
</pre></td></tr></tbody></table><p>Combining object construction and stream opening in a single statement. Both forms to open a file are valid and equivalent.</p><p>To check if a file stream was successful opening a file, you can do it by calling to member <tt>is_open()</tt>
with no arguments. This member function returns a bool value of true in
the case that indeed the stream object is associated with an open file,
or false otherwise:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre><span class="kw">if</span> (myfile.is_open()) { <span class="comm">/* ok, proceed with output */</span> }
</pre></td></tr></tbody></table><p></p><h3>Closing a file</h3>
When we are finished with our input and output operations on a file we
shall close it so that its resources become available again. In order
to do that we have to call the stream's member function <tt>close()</tt>. This member function takes no parameters, and what it does is to flush the associated buffers and close the file:<p></p><table class="snippet"><tbody><tr><td class="code"><pre>myfile.close();
</pre></td></tr></tbody></table><p>Once this member function is called,
the stream object can be used to open another file, and the file is
available again to be opened by other processes.</p><p>In case that an
object is destructed while still associated with an open file, the
destructor automatically calls the member function <tt>close()</tt>.</p><p></p><h3>Text files</h3>
Text file streams are those where we do not include the <tt>ios::binary</tt>
flag in their opening mode. These files are designed to store text and
thus all values that we input or output from/to them can suffer some
formatting transformations, which do not necessarily correspond to
their literal binary value.<p>Data output operations on text files are performed in the same way we operated with <tt>cout</tt>:</p><p></p><table class="codebox"><tbody><tr><td class="code"><pre><span class="comm">// writing on a text file</span>
<span class="prep">#include &lt;iostream&gt;</span>
<span class="prep">#include &lt;fstream&gt;</span>
<span class="kw">using</span> <span class="kw">namespace</span> std;

<span class="kw">int</span> main () {
  ofstream myfile (<span class="str">"example.txt"</span>);
  <span class="kw">if</span> (myfile.is_open())
  {
    myfile &lt;&lt; <span class="str">"This is a line.\n"</span>;
    myfile &lt;&lt; <span class="str">"This is another line.\n"</span>;
    myfile.close();
  }
  <span class="kw">else</span> cout &lt;&lt; <span class="str">"Unable to open file"</span>;
  <span class="kw">return</span> 0;
}
</pre></td><td class="result"><pre>[file example.txt]
This is a line.
This is another line.
</pre></td></tr></tbody></table><p>Data input from a file can also be performed in the same way that we did with <tt>cin</tt>:</p><p></p><table class="codebox"><tbody><tr><td class="code"><pre><span class="comm">// reading a text file</span>
<span class="prep">#include &lt;iostream&gt;</span>
<span class="prep">#include &lt;fstream&gt;</span>
<span class="prep">#include &lt;string&gt;</span>
<span class="kw">using</span> <span class="kw">namespace</span> std;

<span class="kw">int</span> main () {
  string line;
  ifstream myfile (<span class="str">"example.txt"</span>);
  <span class="kw">if</span> (myfile.is_open())
  {
    <span class="kw">while</span> (! myfile.eof() )
    {
      getline (myfile,line);
      cout &lt;&lt; line &lt;&lt; endl;
    }
    myfile.close();
  }

  <span class="kw">else</span> cout &lt;&lt; <span class="str">"Unable to open file"</span>; 

  <span class="kw">return</span> 0;
}
</pre></td><td class="result"><pre>This is a line.
This is another line.  
</pre></td></tr></tbody></table><p>This last example reads a text file
and prints out its content on the screen. Notice how we have used a new
member function, called <tt>eof()</tt> that returns true in the case
that the end of the file has been reached. We have created a while loop
that finishes when indeed <tt>myfile.eof()</tt> becomes true (i.e., the end of the file has been reached).</p><p></p><h3>Checking state flags</h3>
In addition to <tt>eof()</tt>,
which checks if the end of file has been reached, other member
functions exist to check the state of a stream (all of them return a
bool value): <p></p><dl>
<dt>bad()</dt>
<dd>Returns true if a reading or writing operation fails. For example
in the case that we try to write to a file that is not open for writing
or if the device where we try to write has no space left.</dd>
<dt>fail()</dt>
<dd>Returns true in the same cases as bad(), but also in the case that
a format error happens, like when an alphabetical character is
extracted when we are trying to read an integer number.</dd>
<dt>eof()</dt>
<dd>Returns true if a file open for reading has reached the end.</dd>
<dt>good()</dt>
<dd>It is the most generic state flag: it returns false in the same
cases in which calling any of the previous functions would return true.</dd>
</dl><p>In order to reset the state flags checked by any of these member functions we have just seen we can use the member function <tt>clear()</tt>, which takes no parameters.</p><p></p><h3>get and put stream pointers</h3>
All i/o streams objects have, at least, one internal stream pointer:<p><tt>ifstream</tt>, like <tt>istream</tt>, has a pointer known as the <i>get pointer</i> that points to the element to be read in the next input operation.</p><p><tt>ofstream</tt>, like <tt>ostream</tt>, has a pointer known as the <i>put pointer</i> that points to the location where the next element has to be written.</p><p>Finally, <tt>fstream</tt>, inherits both, the get and the put pointers, from <tt>iostream</tt> (which is itself derived from both <tt>istream</tt> and <tt>ostream</tt>).</p><p>These
internal stream pointers that point to the reading or writing locations
within a stream can be manipulated using the following member
functions: </p><p></p><h4>tellg() and tellp()</h4>
These two member functions have no parameters and return a value of the member type <tt>pos_type</tt>, which is an integer data type representing the current position of the get stream pointer (in the case of <tt>tellg</tt>) or the put stream pointer (in the case of <tt>tellp</tt>).<p></p><h4>seekg() and seekp()</h4>
These functions allow us to change the position of the get and put
stream pointers. Both functions are overloaded with two different
prototypes. The first prototype is:<p><tt>
seekg ( position );<br>seekp ( position );<br></tt></p><p>Using this prototype the stream pointer is changed to the absolute position <tt>position</tt> (counting from the beginning of the file). The type for this parameter is the same as the one returned by functions <tt>tellg</tt> and <tt>tellp</tt>: the member type <tt>pos_type</tt>, which is an integer value.</p><p>The other prototype for these functions is:</p><p><tt>
seekg ( offset, direction );<br>seekp ( offset, direction );<br></tt></p><p>Using
this prototype, the position of the get or put pointer is set to an
offset value relative to some specific point determined by the
parameter <tt>direction</tt>. <tt>offset</tt> is of the member type <tt>off_type</tt>, which is also an integer type. And <tt>direction</tt> is of type <tt>seekdir</tt>, which is an enumerated type (<tt>enum</tt>) that determines the point from where offset is counted from, and that can take any of the following values:</p><p></p><table class="boxed">
<tbody><tr><td>ios::beg</td><td>offset counted from the beginning of the stream</td></tr>
<tr><td>ios::cur</td><td>offset counted from the current position of the stream pointer</td></tr>
<tr><td>ios::end</td><td>offset counted from the end of the stream</td></tr>
</tbody></table><p>The following example uses the member functions we have just seen to obtain the size of a file: </p><p></p><table class="codebox"><tbody><tr><td class="code"><pre><span class="comm">// obtaining file size</span>
<span class="prep">#include &lt;iostream&gt;</span>
<span class="prep">#include &lt;fstream&gt;</span>
<span class="kw">using</span> <span class="kw">namespace</span> std;

<span class="kw">int</span> main () {
  <span class="kw">long</span> begin,end;
  ifstream myfile (<span class="str">"example.txt"</span>);
  begin = myfile.tellg();
  myfile.seekg (0, ios::end);
  end = myfile.tellg();
  myfile.close();
  cout &lt;&lt; <span class="str">"size is: "</span> &lt;&lt; (end-begin) &lt;&lt; <span class="str">" bytes.\n"</span>;
  <span class="kw">return</span> 0;
}
</pre></td><td class="result"><pre>size is: 40 bytes.
</pre></td></tr></tbody></table><p></p><h3>Binary files</h3>
In binary files, to input and output data with the extraction and insertion operators (<tt>&lt;&lt;</tt> and <tt>&gt;&gt;</tt>) and functions like <tt>getline</tt>
is not efficient, since we do not need to format any data, and data may
not use the separation codes used by text files to separate elements
(like space, newline, etc...).<p>File streams include two member functions specifically designed to input and output binary data sequentially: <tt>write</tt> and <tt>read</tt>. The first one (<tt>write</tt>) is a member function of <tt>ostream</tt> inherited by <tt>ofstream</tt>. And <tt>read</tt> is a member function of <tt>istream</tt> that is inherited by <tt>ifstream</tt>. Objects of class <tt>fstream</tt> have both members. Their prototypes are:</p><p><tt>
write ( memory_block, size );<br>read ( memory_block, size );<br></tt></p><p>Where <tt>memory_block</tt> is of type "pointer to char" (<tt>char*</tt>),
and represents the address of an array of bytes where the read data
elements are stored or from where the data elements to be written are
taken. The <tt>size</tt> parameter is an integer value that specifies the number of characters to be read or written from/to the memory block.</p><p></p><table class="codebox"><tbody><tr><td class="code"><pre><span class="comm">// reading a complete binary file</span>
<span class="prep">#include &lt;iostream&gt;</span>
<span class="prep">#include &lt;fstream&gt;</span>
<span class="kw">using</span> <span class="kw">namespace</span> std;

ifstream::pos_type size;
<span class="kw">char</span> * memblock;

<span class="kw">int</span> main () {
  ifstream file (<span class="str">"example.txt"</span>, ios::in|ios::binary|ios::ate);
  <span class="kw">if</span> (file.is_open())
  {
    size = file.tellg();
    memblock = <span class="kw">new</span> <span class="kw">char</span> [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    cout &lt;&lt; <span class="str">"the complete file content is in memory"</span>;

    <span class="kw">delete</span>[] memblock;
  }
  <span class="kw">else</span> cout &lt;&lt; <span class="str">"Unable to open file"</span>;
  <span class="kw">return</span> 0;
}
</pre></td><td class="result"><pre>the complete file content is in memory
</pre></td></tr></tbody></table><p>In this example the entire file is read and stored in a memory block. Let's examine how this is done:</p><p>First, the file is open with the <tt>ios::ate</tt> flag, which means that the get pointer will be positioned at the end of the file. This way, when we call to member <tt>tellg()</tt>, we will directly obtain the size of the file. Notice the type we have used to declare variable <tt>size</tt>:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre>ifstream::pos_type size;
</pre></td></tr></tbody></table><p><tt>ifstream::pos_type</tt> is a specific type used for buffer and file positioning and is the type returned by <tt>file.tellg()</tt>.
This type is defined as an integer type, therefore we can conduct on it
the same operations we conduct on any other integer value, and can
safely be converted to another integer type large enough to contain the
size of the file. For a file with a size under 2GB we could use <tt>int</tt>:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre><span class="kw">int</span> size;
size = (<span class="kw">int</span>) file.tellg();
</pre></td></tr></tbody></table><p>Once we have obtained the size of the file, we request the allocation of a memory block large enough to hold the entire file:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre>memblock = <span class="kw">new</span> <span class="kw">char</span>[size];
</pre></td></tr></tbody></table><p>Right after that, we proceed to set
the get pointer at the beginning of the file (remember that we opened
the file with this pointer at the end), then read the entire file, and
finally close it:</p><p></p><table class="snippet"><tbody><tr><td class="code"><pre>file.seekg (0, ios::beg);
file.read (memblock, size);
file.close();
</pre></td></tr></tbody></table><p>At this point we could operate with
the data obtained from the file. Our program simply announces that the
content of the file is in memory and then terminates.</p><p></p><h3>Buffers and Synchronization</h3><p>When we operate with file streams, these are associated to an internal buffer of type <tt>streambuf</tt>. This buffer is a memory block that acts as an intermediary between the stream and the physical file. For example, with an <tt>ofstream</tt>, each time the member function <tt>put</tt>
(which writes a single character) is called, the character is not
written directly to the physical file with which the stream is
associated. Instead of that, the character is inserted in that stream's
intermediate buffer.</p><p>When the buffer is flushed, all the data
contained in it is written to the physical medium (if it is an output
stream) or simply freed (if it is an input stream). This process is
called <i>synchronization</i> and takes place under any of the following circumstances: </p><p></p><ul>
<li><b>When the file is closed:</b> before closing a file all buffers
that have not yet been flushed are synchronized and all pending data is
written or read to the physical medium.</li>
<li><b>When the buffer is full:</b> Buffers have a certain size. When the buffer is full it is automatically synchronized.</li>
<li><b>Explicitly, with manipulators:</b> When certain manipulators are used on streams, an explicit synchronization takes place. These manipulators are: <tt>flush</tt> and <tt>endl</tt>.</li>
<li><b>Explicitly, with member function sync():</b> Calling stream's member function <tt>sync()</tt>, which takes no parameters, causes an immediate synchronization. This function returns an <tt>int</tt> value equal to <tt>-1</tt>
if the stream has no associated buffer or in case of failure. Otherwise
(if the stream buffer was successfully synchronized) it returns <tt>0</tt>.</li>
</ul>
<p></p><center><table><tbody><tr><td align="right" width="49%"><a href="http://www.cplusplus.com/doc/tutorial/preprocessor.html"><img src="file_io_cplusplus_files/navigate_previous.gif" align="right" border="0">Previous:<br><b>Preprocessor directives</b></a> </td><td><a href="http://www.cplusplus.com/doc/tutorial/"><img src="file_io_cplusplus_files/navigate_index.gif" border="0"><br>index</a></td><td align="left" width="49%"> </td></tr></tbody></table></center><p>
<script type="text/javascript">
<!--
SuOptions()
-->
</script></p><script type="text/javascript"><!--
google_ad_client = "pub-5777024789006368";
google_ad_width = 728;
google_ad_height = 90;
google_ad_format = "728x90_as";
google_ad_type = "text_image";
google_ad_channel = "5575794683";
google_color_border = "FFFFFF";
google_color_bg = "FFFFFF";
google_color_link = "3333CC";
google_color_text = "000000";
google_color_url = "000000";
//--></script>
<script type="text/javascript" src="file_io_cplusplus_files/show_ads.js">
</script><iframe name="google_ads_frame" src="file_io_cplusplus_files/ads_002.htm" marginwidth="0" marginheight="0" vspace="0" hspace="0" allowtransparency="true" frameborder="0" height="90" scrolling="no" width="728"></iframe>
</div>
</td>



</tr>
<tr><td colspan="2" style="border-top: 1px solid black; background: rgb(215, 215, 215) none repeat scroll 0%; padding-bottom: 5px; -moz-background-clip: -moz-initial; -moz-background-origin: -moz-initial; -moz-background-inline-policy: -moz-initial;" align="center"><small>© The C++ Resources Network, 2000-2007 - All rights reserved<br><a href="http://www.cplusplus.com/member/contact.form?referrer=http://www.cplusplus.com/doc/tutorial/files.html">Spotted an error? - contact us</a></small></td></tr>
</tbody></table>

<script src="file_io_cplusplus_files/urchin.js" type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-521783-1";
urchinTracker();
</script>
</body></html>