qwget
=====

Extremely simple blocking wrapper under QNetworkManager, allowing 'quick&amp;dirty' data acquire from internet hosts

usage
-----

In Your .pro file, write:
 
    qwget_root = ../qwget # or other place You've checked out qwget
    include($$qwget_root/qwget.pri)

In Your code, write:

    QWget wget;
    QByteArray answer  = wget("http://google.com"); 
    // Now, there is web page contents in answer variable
    
