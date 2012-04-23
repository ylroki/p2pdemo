<map version="0.9.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1294123845969" ID="ID_1125410527" LINK="../downloader/network/doc/kugou7-network.mm" MODIFIED="1332303747094" TEXT="p2p">
<node CREATED="1331536121632" HGAP="93" ID="ID_452468075" MODIFIED="1331725105314" POSITION="left" TEXT="protocol" VSHIFT="-76">
<node CREATED="1333608493627" ID="ID_133646571" MODIFIED="1333608499997" TEXT="centralized">
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
</html></richcontent>
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
</html></richcontent>
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
</html></richcontent>
</node>
<node CREATED="1331538970928" ID="ID_115023932" MODIFIED="1332937285333" TEXT="0x32 file data">
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
      long|4|block offset start
    </p>
    <p>
      long|4|size of content
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
<arrowlink DESTINATION="ID_1867565399" ENDARROW="Default" ENDINCLINATION="41;0;" ID="Arrow_ID_372405882" STARTARROW="None" STARTINCLINATION="41;0;"/>
</node>
<node CREATED="1331538708024" ID="ID_30407450" MODIFIED="1332937285332" TEXT="0x22 get file data">
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
      long|4|block offset start
    </p>
    <p>
      long|4|block offset end
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_115023932" ENDARROW="Default" ENDINCLINATION="55;0;" ID="Arrow_ID_162728" STARTARROW="None" STARTINCLINATION="55;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1333608501060" ID="ID_367242997" MODIFIED="1333608506491" TEXT="distributed">
<node CREATED="1333966381550" ID="ID_161383535" MODIFIED="1333966429655" TEXT="PING">
<node CREATED="1333966431524" ID="ID_591167117" MODIFIED="1334906411743" TEXT="0x40 request">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x40
    </p>
    <p>
      unsigned char*|16|self node id
    </p>
    <p>
      short|2|task id
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1333966634285" ID="ID_1197635002" MODIFIED="1334906397173" TEXT="0x41 response">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x41
    </p>
    <p>
      unsigned char*|16|self id
    </p>
    <p>
      short|2|task id
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1333966717270" ID="ID_248471927" MODIFIED="1333966721170" TEXT="STORE">
<node CREATED="1333966752097" ID="ID_1751865941" MODIFIED="1333967317026" TEXT="0x42 request">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x42
    </p>
    <p>
      unsigned char*|16|key
    </p>
    <p>
      char|1|bytes of value n
    </p>
    <p>
      char*|n|value
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1333966946247" ID="ID_1345643335" MODIFIED="1333966953194" TEXT="FIND_NODE">
<node CREATED="1333966954623" ID="ID_1805642487" MODIFIED="1333967466614" TEXT="0x44 reuqest">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x44
    </p>
    <p>
      unsigned char*|16|node id
    </p>
    <p>
      unsigned long|4|rpc id
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1333967008624" ID="ID_1178483210" MODIFIED="1333968096922" TEXT="0x45 response">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x45
    </p>
    <p>
      unsigned char*|16|node id
    </p>
    <p>
      unsigned long|4|rpc id
    </p>
    <p>
      char|1|number of node info
    </p>
    <p>
      node info|n|nodes
    </p>
    <p>
      
    </p>
    <p>
      for each node
    </p>
    <p>
      unsigned logn|4|ip
    </p>
    <p>
      unsgned short|2|port
    </p>
    <p>
      unsigned char*|16|node id
    </p>
  </body>
</html></richcontent>
</node>
</node>
<node CREATED="1333967637033" ID="ID_742590445" MODIFIED="1333967642332" TEXT="FIND_VALUE">
<node CREATED="1333967656632" ID="ID_1908773177" MODIFIED="1333967678403" TEXT="0x46 request">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x46
    </p>
    <p>
      unsigned char*|16|key
    </p>
    <p>
      unsigned long|4|rpc id
    </p>
    <p>
      
    </p>
  </body>
</html></richcontent>
</node>
<node CREATED="1333967683517" ID="ID_1202478694" MODIFIED="1333968169235" TEXT="0x47 response">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      char|1|0x47
    </p>
    <p>
      unsigned char*|16|key
    </p>
    <p>
      unsigned long|4|rpc id
    </p>
    <p>
      char|1|bytes of value n
    </p>
    <p>
      char*|n|value
    </p>
    <p>
      
    </p>
    <p>
      note: if recipient doesn't have &lt;key, value&gt;, response 0x45 instead.
    </p>
    <p>
      
    </p>
    <p>
      
    </p>
  </body>
</html></richcontent>
</node>
</node>
</node>
</node>
<node CREATED="1333608346431" ID="ID_811177061" MODIFIED="1333608430149" POSITION="right" TEXT="centralized">
<node CREATED="1331718349073" ID="ID_818234251" MODIFIED="1331718360754" TEXT="clientd">
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
</html></richcontent>
<arrowlink DESTINATION="ID_1721342018" ENDARROW="Default" ENDINCLINATION="922;0;" ID="Arrow_ID_307573770" STARTARROW="None" STARTINCLINATION="922;0;"/>
</node>
<node CREATED="1331720938686" ID="ID_660665471" MODIFIED="1331722836936" TEXT="UpdateSource()">
<node CREATED="1332841548096" ID="ID_988285582" MODIFIED="1332841561220" TEXT="send 0x21 check"/>
<node CREATED="1332935460428" ID="ID_1141091011" MODIFIED="1332936287303" TEXT="RequestFileData()">
<arrowlink DESTINATION="ID_980837094" ENDARROW="Default" ENDINCLINATION="632;0;" ID="Arrow_ID_567257821" STARTARROW="None" STARTINCLINATION="632;0;"/>
</node>
</node>
<node CREATED="1331720991202" ID="ID_612826724" MODIFIED="1331722839768" TEXT="SelectSocket()">
<node CREATED="1331722861419" ID="ID_1107248652" MODIFIED="1331722872312" TEXT="RecvMessage()">
<node CREATED="1332841393034" ID="ID_420994736" MODIFIED="1332841568415" TEXT="recv 0x14 ">
<node CREATED="1332841477931" ID="ID_546972142" MODIFIED="1332841492713" TEXT="DealSourceResponse()"/>
</node>
<node CREATED="1332841710021" ID="ID_1314315164" MODIFIED="1332841723039" TEXT="recv 0x31">
<node CREATED="1332841749614" ID="ID_1281261928" MODIFIED="1332841762327" TEXT="DealCheckResult()"/>
</node>
<node CREATED="1332937117740" ID="ID_384956420" MODIFIED="1332937121674" TEXT="recv 0x32">
<node CREATED="1332937125222" ID="ID_1669097700" MODIFIED="1332937143179" TEXT="DealFileData()"/>
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
</html></richcontent>
<arrowlink DESTINATION="ID_1314315164" ENDARROW="Default" ENDINCLINATION="666;0;" ID="Arrow_ID_635281787" STARTARROW="None" STARTINCLINATION="666;0;"/>
</node>
<node CREATED="1332935488329" ID="ID_980837094" MODIFIED="1332937143180" TEXT="recv 0x22">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      upload-&gt;GetFileData()
    </p>
  </body>
</html></richcontent>
<arrowlink DESTINATION="ID_1669097700" ENDARROW="Default" ENDINCLINATION="789;0;" ID="Arrow_ID_828635562" STARTARROW="None" STARTINCLINATION="789;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1331724826200" ID="ID_1182121130" MODIFIED="1331724832350" TEXT="logout"/>
</node>
<node CREATED="1331718370679" ID="ID_1537597852" MODIFIED="1331718375749" TEXT="server">
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
</html></richcontent>
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
</html></richcontent>
<arrowlink DESTINATION="ID_420994736" ENDARROW="Default" ENDINCLINATION="1053;0;" ID="Arrow_ID_1121048093" STARTARROW="None" STARTINCLINATION="1053;0;"/>
</node>
</node>
</node>
</node>
<node CREATED="1333608432601" ID="ID_675602145" MODIFIED="1333608445696" POSITION="right" TEXT="distributed">
<node CREATED="1333608547261" ID="ID_1309283155" MODIFIED="1333608554418" TEXT="client">
<node CREATED="1334840166853" ID="ID_156987318" MODIFIED="1334840176728" TEXT="CalculateClientID()"/>
<node CREATED="1333608931103" ID="ID_933237317" MODIFIED="1333932733215" TEXT="a thread run Work()">
<node CREATED="1333857065456" ID="ID_810058114" MODIFIED="1333965912290" TEXT="JoinKad()">
<node CREATED="1334160185359" ID="ID_1360847760" MODIFIED="1334160197785" TEXT="InitTable()"/>
<node CREATED="1334839040226" ID="ID_714234791" MODIFIED="1334840103810" TEXT="Add task:find node"/>
</node>
<node CREATED="1333857086971" ID="ID_408650764" MODIFIED="1333932771452" TEXT="loop while !m_Stopped">
<node CREATED="1333932774772" ID="ID_1770515548" MODIFIED="1334811679570" TEXT="Republish()">
<node CREATED="1334811682226" ID="ID_1203529276" MODIFIED="1334811717660" TEXT="for each key,vaue in database, RepublishHelper()">
<node CREATED="1334811730880" ID="ID_207510756" MODIFIED="1334901422547" TEXT="Add task:simple store"/>
</node>
</node>
<node CREATED="1333932829636" ID="ID_775369101" MODIFIED="1334811765738" TEXT="Refresh()">
<node CREATED="1334811800632" ID="ID_1406382781" MODIFIED="1334901408781" TEXT="for each node in k-bucket, Add task:ping"/>
</node>
<node CREATED="1334811328631" ID="ID_497397113" MODIFIED="1334812077661" TEXT="CTaskManager::Update()">
<node CREATED="1334812079344" ID="ID_722324577" MODIFIED="1334812090552" TEXT="for each task, Update()"/>
</node>
<node CREATED="1334911018357" ID="ID_883586064" MODIFIED="1334911030632" TEXT="SelectSocket()"/>
</node>
</node>
<node CREATED="1333932992803" ID="ID_396502490" MODIFIED="1333933013261" TEXT="some interface for invoking">
<node CREATED="1334039800832" ID="ID_200148782" MODIFIED="1334044659552" TEXT="FindSource">
<node CREATED="1334040159891" ID="ID_152044803" MODIFIED="1334040187979" TEXT="if key is in local database">
<node CREATED="1334040188699" ID="ID_128180783" MODIFIED="1334040203607" TEXT="yes: return value"/>
<node CREATED="1334040204368" ID="ID_1348277534" MODIFIED="1334901395959" TEXT="no: Add task:find value, but the function return directly"/>
</node>
</node>
</node>
</node>
</node>
<node CREATED="1335164922112" ID="ID_1201415244" MODIFIED="1335164931387" POSITION="left" TEXT="CTask">
<node CREATED="1335164933265" ID="ID_1963770320" MODIFIED="1335164944615" TEXT="CTaskPing">
<node CREATED="1335164977081" ID="ID_1297411720" MODIFIED="1335164988162" TEXT="PS_INIT">
<node CREATED="1335171111200" ID="ID_62513496" MODIFIED="1335171147747" TEXT="send PING request, then turn to PS_WAIT"/>
</node>
<node CREATED="1335164989586" ID="ID_139994708" MODIFIED="1335164997356" TEXT="PS_WAIT">
<node CREATED="1335171150570" ID="ID_109561565" MODIFIED="1335171177095" TEXT="if time out, delete node and turn to PS_END"/>
<node CREATED="1335171179193" ID="ID_114703693" MODIFIED="1335171209769" TEXT="Process() will also turn status into PS_END"/>
</node>
<node CREATED="1335165006006" ID="ID_1604653739" MODIFIED="1335165010805" TEXT="PS_END">
<node CREATED="1335171212627" ID="ID_853909633" MODIFIED="1335171228323" TEXT="set m_IsStopped true"/>
</node>
</node>
</node>
</node>
</map>
