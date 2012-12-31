function randord(a, b){ return (Math.round(Math.random())-0.5); }
var ent = new Array(); var ii = 0;
ent[ii++] = '<a href="contact.php"><img src="img\/mail.gif" width="34" height="18" alt="Send us an Email" border="0" \/> Contact Us<\/a>';
ent[ii++] = '<a href="tell.htm"><img src="img\/tell.gif" width="40" height="20" alt="Tell a friend about this site" border="0" \/> Tell a Friend<\/a>';
ent[ii++] = '<a href="testimon.htm"><img src="img\/writit2.gif" width="32" height="31" alt="Read others comments about our site" border="0" \/> Testimonials<\/a>';
ent[ii++] = '<a href="fav.htm"><img src="img\/fav.gif" width="32" height="32" alt="Your Favourite Pages" border="0" \/> Your Favourites<\/a>';
ent[ii++] = '<a href="ask.htm"><img src="img\/ask.gif" width="24" height="32" alt="Ask us a Question" border="0" \/> Ask Felgall<\/a>';
ent[ii++] = '<a href="forum.php"><img src="img\/writit1.gif" width="32" height="30" alt="Ask or Answer a Question" border="0" \/> Forums<\/a>';
ent[ii++] = '<a href="bts.htm"><img src="img\/list.gif" width="30" height="28" alt="Sign up for our monthly newsletter - \'Behind the Scenes\'" border="0" \/> Newsletter<\/a>';
ent[ii++] = '<a href="guestlst.php" onclick="newWindow(\'guestmap.php\');"><img src="img\/map1.gif" width="32" height="16" alt="Sign our Guestbook/Make your mark on our Guestmap" border="0" \/> Guestmap<\/a>';
ent[ii++] = '<a href="gloss.htm"><img src="img\/gloss.gif" width="31" height="32" alt="Don\'t understand a computer term, look it up here" border="0" \/> Glossary<\/a>';
ent.sort(randord);
document.writeln('<div align="center">' + ent[0] + '<img src="img\/1x1shim.gif" height="1" width="40" alt="" \/>' + ent[1] + '<\/div>');
var myDate = new Date; var thisyear = myDate.getFullYear();
document.writeln('<div align="center"><i>');if (uri.page == 'index'){document.writeln('This site was "born" on 20th October 2000');}document.writeln('<\/i><\/span>');if (uri.page != 'steve' && uri.page != 'book') document.write('<br /><a href="disc.htm">Copyright &copy; 2000 - ' + thisyear + ' Felgall Pty Ltd<\/a>'); document.write('<\/div>');
document.writeln('<p align="center"><span class="tiny"><i><a href="http:\/\/www.icra.org\/labelv02.html" target="_blank" class="ext">ICRA<\/a> - Rating Labels - <a href="http:\/\/www.safesurf.com\/" target="_blank" class="ext">SafeSurf</a><\/i><\/span><\/p>');
