<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1294123845969" ID="ID_1125410527" LINK="../downloader/network/doc/kugou7-network.mm" MODIFIED="1332303747094" TEXT="p2p">
<node CREATED="1331536121632" HGAP="93" ID="ID_452468075" MODIFIED="1331725105314" POSITION="left" TEXT="protocol" VSHIFT="-76">
<node CREATED="1331538146425" ID="ID_398814164" MODIFIED="1331538155571" TEXT="C/S">
<node CREATED="1331536137006" ID="ID_158097607" MODIFIED="1331536158912" TEXT="server">
<node CREATED="1331536178567" HGAP="152" ID="ID_1594695151" MODIFIED="1331538120553" TEXT="send" VSHIFT="-41">
<node CREATED="1331537386946" ID="ID_91180679" MODIFIED="1332841260173" TEXT="0x13 search result">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x13
    </p>
    <p>
      char|1|size of search key string
    </p>
    <p>
      char|s|string
    </p>
    <p>
      char|1|numbers of hashes
    </p>
    <p>
      char|16*n|hashes
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1331537743081" ID="ID_1704814405" MODIFIED="1332841253551" TEXT="0x14 request result">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x14
    </p>
    <p>
      char|16|hash
    </p>
    <p>
      unsigned long|4|file size<br />char|1|number of sources
    </p>
    <p>
      source|6*n|sources
    </p>
    <p>
      
    </p>
    <p>
      in each source
    </p>
    <p>
      long|4|ip
    </p>
    <p>
      short|2|port
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1331536159778" ID="ID_1350210120" MODIFIED="1331536162340" TEXT="client">
<node CREATED="1331536206630" HGAP="148" ID="ID_1221378393" MODIFIED="1331538126477" TEXT="send" VSHIFT="26">
<node CREATED="1331536430903" ID="ID_1358088132" MODIFIED="1332841242354" TEXT="0x01 login">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x01
    </p>
    <p>
      unsigned short|2|peerPort
    </p>
    <p>
      unsigned long|4|numbers of hashes
    </p>
    <p>
      unsigned char*|20*n|hashes
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1331536441888" ID="ID_588323776" MODIFIED="1332841248291" TEXT="0x02 logout">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x02
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1331536219942" HGAP="46" ID="ID_18803556" MODIFIED="1332841266393" TEXT="0x3 search by key" VSHIFT="-19">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x03
    </p>
    <p>
      char|1|size of search string, include terminal NULL
    </p>
    <p>
      char|size|search string, terminated by NULL
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_91180679" ENDARROW="Default" ENDINCLINATION="95;0;" ID="Arrow_ID_218409333" STARTARROW="None" STARTINCLINATION="95;0;"/>
</node>
<node CREATED="1331537658001" ID="ID_1898748950" MODIFIED="1332841273447" TEXT="0x04 request source of a hash">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x04
    </p>
    <p>
      unsigned char*|16|hash
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_1704814405" ENDARROW="Default" ENDINCLINATION="148;0;" ID="Arrow_ID_928873851" STARTARROW="None" STARTINCLINATION="148;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1331538175051" ID="ID_1798528038" MODIFIED="1331538183609" TEXT="P/P">
<node CREATED="1331538212259" ID="ID_326672241" MODIFIED="1331538223319" TEXT="source peer">
<node CREATED="1331538364484" ID="ID_1867565399" MODIFIED="1332841284453" TEXT="0x31 check result">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x31
    </p>
    <p>
      unsigned char*|16|hash
    </p>
    <p>
      unsigned long|4|sessionID
    </p>
    <p>
      char|1|status
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1331538970928" ID="ID_115023932" MODIFIED="1332841309132" TEXT="0x32 file data">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x32
    </p>
    <p>
      unsigned c*har|16|hash
    </p>
    <p>
      char|1|block size, 1 means 1k
    </p>
    <p>
      long|4|block offset start
    </p>
    <p>
      long|4|block offset end
    </p>
    <p>
      char*|*|content
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1331538224166" ID="ID_804188050" MODIFIED="1331538242720" TEXT="request peer">
<node CREATED="1331538258953" ID="ID_1525254213" MODIFIED="1332841304250" TEXT="0x21 check">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x21
    </p>
    <p>
      unsigned char*|16|hash
    </p>
    <p>
      unsigned long|4|sessionID
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_1867565399" ENDARROW="Default" ENDINCLINATION="41;0;" ID="Arrow_ID_1492304979" STARTARROW="None" STARTINCLINATION="41;0;"/>
</node>
<node CREATED="1331538708024" ID="ID_30407450" MODIFIED="1332841317844" TEXT="0x22 get file data">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|commandID|0x22
    </p>
    <p>
      unsigned char*|16|hash
    </p>
    <p>
      char|1|block size, 1 means 1k
    </p>
    <p>
      long|4|block offset start
    </p>
    <p>
      long|4|block offset end
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_115023932" ENDARROW="Default" ENDINCLINATION="55;0;" ID="Arrow_ID_916413121" STARTARROW="None" STARTINCLINATION="55;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1331718349073" ID="ID_818234251" MODIFIED="1331718360754" POSITION="right" TEXT="clientd">
<node CREATED="1331717812339" ID="ID_135490889" MODIFIED="1331717822111" TEXT="get config"/>
<node CREATED="1331725326750" ID="ID_186251771" MODIFIED="1331725420275" TEXT="a thread run CFileSystem::Work()">
<node CREATED="1331725111450" ID="ID_1128952668" MODIFIED="1331725148131" TEXT="loop every update period(in config)">
<node CREATED="1331725162896" ID="ID_241328780" MODIFIED="1331725234752" TEXT="FindResources()">
<node CREATED="1332840662308" ID="ID_496928858" MODIFIED="1332840685910" TEXT="insert each md5 into database"/>
<node CREATED="1332840706545" ID="ID_1403183032" MODIFIED="1332841059217" TEXT="0x01 login">
<arrowlink DESTINATION="ID_375580266" ENDARROW="Default" ENDINCLINATION="527;0;" ID="Arrow_ID_1926982400" STARTARROW="None" STARTINCLINATION="527;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1331384437318" ID="ID_867771177" MODIFIED="1331535513677" TEXT="daemonize, and bind a socket listenning local command">
<node CREATED="1331384492367" ID="ID_1930825075" MODIFIED="1331535719411" TEXT="download">
<node CREATED="1328357159533" ID="ID_1452656903" MODIFIED="1328357262650" TEXT="a thread run function CDownload::Work()">
<node CREATED="1331720240009" ID="ID_754123345" MODIFIED="1331720251947" TEXT="initialize socket"/>
<node CREATED="1331263372420" ID="ID_274205583" MODIFIED="1331720907118" TEXT="loop while m_Status == DS_RUNNING">
<node CREATED="1331720925441" ID="ID_454207595" MODIFIED="1332841193994" TEXT="RequestSource()">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      0x04
    </p>
  </body>
</html>
</richcontent>
<arrowlink DESTINATION="ID_1721342018" ENDARROW="Default" ENDINCLINATION="922;0;" ID="Arrow_ID_307573770" STARTARROW="None" STARTINCLINATION="922;0;"/>
</node>
<node CREATED="1331720938686" ID="ID_660665471" MODIFIED="1331722836936" TEXT="UpdateSource()">
<node CREATED="1332841548096" ID="ID_988285582" MODIFIED="1332841561220" TEXT="send 0x21 check"/>
</node>
<node CREATED="1331720991202" ID="ID_612826724" MODIFIED="1331722839768" TEXT="SelectSocket()">
<node CREATED="1331722861419" ID="ID_1107248652" MODIFIED="1331722872312" TEXT="RecvMessage()">
<node CREATED="1332841393034" ID="ID_420994736" MODIFIED="1332841568415" TEXT="recv 0x14 ">
<node CREATED="1332841477931" ID="ID_546972142" MODIFIED="1332841492713" TEXT="DealSourceResponse()"/>
</node>
<node CREATED="1332841710021" ID="ID_1314315164" MODIFIED="1332841723039" TEXT="recv 0x31">
<node CREATED="1332841749614" ID="ID_1281261928" MODIFIED="1332841762327" TEXT="DealCheckResult()"/>
</node>
</node>
</node>
</node>
</node>
</node>
<node CREATED="1331384567726" ID="ID_913106098" MODIFIED="1331384569795" TEXT="stop"/>
</node>
<node CREATED="1331384524036" ID="ID_825897321" MODIFIED="1331718488601" TEXT="a thread run CUploadFile::Work()">
<node CREATED="1331535412289" ID="ID_880864345" MODIFIED="1331722900832" TEXT="initialize socket"/>
<node CREATED="1331536078766" ID="ID_1393798023" MODIFIED="1331723078250" TEXT="loop while !m_Stopped">
<node CREATED="1331723080198" ID="ID_1357288561" MODIFIED="1331723107125" TEXT="if select, RecvMessage()">
<node CREATED="1332841639735" ID="ID_1887601953" MODIFIED="1332841723040" TEXT="recv 0x21">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      check if file exist or not, send 0x31
    </p>
  </body>
</html>
</richcontent>
<arrowlink DESTINATION="ID_1314315164" ENDARROW="Default" ENDINCLINATION="666;0;" ID="Arrow_ID_457294045" STARTARROW="None" STARTINCLINATION="666;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1331724826200" ID="ID_1182121130" MODIFIED="1331724832350" TEXT="logout"/>
</node>
<node CREATED="1331718370679" ID="ID_1537597852" MODIFIED="1331718375749" POSITION="right" TEXT="server">
<node CREATED="1332840939515" ID="ID_1464996576" MODIFIED="1332840991383" TEXT="deal message">
<node CREATED="1332840997675" ID="ID_375580266" MODIFIED="1332841059216" TEXT="0x01 login">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Insert ip,port,filesize into database
    </p>
  </body>
</html>
</richcontent>
</node>
<node CREATED="1332841158636" ID="ID_1721342018" MODIFIED="1332841428065" TEXT="0x04 request source">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      response 0x14
    </p>
  </body>
</html>
</richcontent>
<arrowlink DESTINATION="ID_420994736" ENDARROW="Default" ENDINCLINATION="1053;0;" ID="Arrow_ID_1121048093" STARTARROW="None" STARTINCLINATION="1053;0;"/>
</node>
</node>
</node>
</node>
</map>
