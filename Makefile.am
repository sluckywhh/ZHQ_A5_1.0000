#AWE-4000R Project
bin_PROGRAMS = awe4000r

awe4000r_SOURCES = main.cpp

EXTRA_DIST = main.cpp

awe4000r_LDADD = ./SERIAL/libserial.a ./APP/libaweapp.a ./APP/YWXML/libaweywxml.a ./APP/COMMON/libawecommon.a ./APP/SKJYWXML/libaweskjywxml.a ./APP/SERVXML/libaweservxml.a ./APP/JSKMANAGE/libawejsk.a ./LIBDB/libawedb.a ./DRV/libawedrv.a ./SYS/libawesys.a ./LIB/libsqlite3.a ./LIB/libz.a ./LIB/libJspInterface_a5.a ./SSLLIB/acceptFramework/lib/libuniAcceptFramework.a  ./SSLLIB/jsp_driver/yiju/Demo/armcryptlib.a ./SSLLIB/cryptopp/lib/libcryptopp.a ./SSLLIB/curl/lib/libcurl.a ./SSLLIB/openssl/lib/libssl.a ./SSLLIB/openssl/lib/libcrypto.a  ./SSLLIB/jsp_driver/subin-lib/WTlib/libwt_skf.a ./SSLLIB/jsp_driver/subin-lib/WTlib/libwt_pkcs11.a  ./SSLLIB/jsp_driver/subin-lib/WTlib/libwt_hw.a  ./SSLLIB/acceptFramework/lib/libaisino_pkcs11_engine.a -lpthread -ldl -lrt

SUBDIRS = SYS SERIAL LIB LIBDB APP DRV 

INCLUDES = -I./SYS -I./LIB -I./LIBDB -I./DRV -I./APP  -I./APP/JSKMANAGE -I./APP/YWXML -I./APP/SERVXML -I./APP/COMMON -I./APP/SKJYWXML -I./SERIAL -I./SSLLIB/acceptFramework/include
