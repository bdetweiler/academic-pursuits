document.writeln('<span style="color:#ffff66;font-size:9pt;">');
if (refdir == 'felgall.com' || refdir == 'www.felgall.com'  || refdir == 'felgall.com.au'  || refdir == 'www.felgall.com.au' || refdir == '' || refdir == 'b' ||  uri.page == 'index') {
if (uri.page != 'index' && uri.page != '') {
var mess = new Array();
mess[0] = 'Sign up for <a href="bts.htm" class="nav">"Behind the Scenes"</a> - Our Newsletter';
mess[1] = 'We can do it for you <a href="quote.htm" class="nav"> click here</a> to ask for a quote';
mess[2] = mess[0];
mess[3] = 'Get a <a href="php2.htm" class="nav">Form to Mail</a> PHP script that supports attachments';
mess[4] = 'See <a href="whatsnew.htm" class="nav">What\'s New</a> on Our Site';
mess[5] = 'Help answer questions in the <a href="forum.php" class="nav">Question Forum</a>';
mess[6] = 'Get a <a href="php2.htm" class="nav">Form to Mail</a> PHP script that supports embedded images';
mess[7] = mess[0];
mess[8] = 'Your Feedback is Welcome - Please <a href="comment.htm" class="nav">send us your comments</a>';
mess[9] = 'Get a <a href="php4.htm" class="nav">Site Search</a> PHP script';
mess[10] = 'Put a <a href="php7.htm" class="nav">Guestmap</a> on your site';
mess[11] = 'Can\'t find the answer - then <a href="ask.htm" class="nav">Ask Felgall</a>';
mess[12] = 'Ask Felgall to <a href="webspec.htm" class="nav">build and maintain your web site.</a>';
mess[13] = 'Don\'t want to do it yourself <a href="quote.htm" class="nav">Ask Felgall for a quote.</a>';
mess[14] = 'Check out our <a href="webspec.htm" class="nav">special offers</a> on web site construction and maintenance';
mess[15] = 'Steve is <a href="job.htm" class="nav">looking for work</a>. Can you help?';
mess[16] = 'Get a <a href="php6a.htm" class="nav">Paypal IPN</a> PHP script';
mess[17] = '<a href="tell.htm" class="nav">Recommend us to Your Friends</a>';
var max = mess.length; var num = Math.floor((Math.random() * max));
document.writeln(mess[num]);
} else
document.writeln('Select a topic category or just search our site.');
} else {
document.writeln('&lt;== Please click on the computer image to visit our home page');
}
document.writeln('</\span><br />');


if (uri.file == 'javatip7.htm') {goNewWin();}