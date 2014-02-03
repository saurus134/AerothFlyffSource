#ifndef __VERSION_COMMON_H__
#define __VERSION_COMMON_H__

#define __ERRORTXT

// exception handler관련
#define __TRANSFER_ERROR_TEXT		// 에러 텍스트를 서버로 보낸다.
#define __MINIMIZE_USE_OPTION		// COption클래스만을 단독 사용한다.
#define __PATCHVER2
#define	ADDR_ACCUMULATOR			"211.33.142.133"

#define LANG_KOR 0
#define LANG_ENG 1
#define LANG_JAP 2
#define LANG_CHI 3
#define LANG_THA 4
#define LANG_TWN 5
#define LANG_GER 6
#define LANG_SPA 7
#define LANG_FRA 8
#define LANG_POR 9
#define LANG_VTN 10
#define LANG_RUS 11

// 국가 정의를 언어권 정의와 값이 겹치지 않도록 한다
#define CNTRY_USA 20
#define CNTRY_PHI 21
#define CNTRY_TWN 22
#define CNTRY_HK  23
#define CNTRY_IND 24

#define __YENV
#define	__YDAMAGE_RENDER
#define	__YVISIBLE_BUFF_TIME
#define __ACROBAT_0504
#define __YGUIDESYSTEM0923
#define __XGLARE
#define __SFX_OPT

// 필요에 따라서 주석문을 풀고 컴파일 해주세요.
// 컴파일이 끝나면 undo check out하시면 됩니다.

//#define __MAINSERVER
//#define __TESTSERVER
//#define __LANG_JAP
	//#define __JAPAN
	//#define __JAPAN_TEST
//#define __LANG_THAI
	//#define __LANG_THAI_MAIN
	//#define __LANG_THAI_TEST
//#define __LANG_TAIWAN
	//#define	__LANG_TAIWAN_MAIN
	//#define	__LANG_TAIWAN_TEST
	//#define	__LANG_TAIWAN_HONGKONG
	//#define	__LANG_TAIWAN_HONGKONG_TEST
#define __LANG_ENG
	//#define __LANG_ENG_PHP
	//#define __LANG_ENG_PHPTEST
	#define __LANG_ENG_USA
	//#define __LANG_ENG_USATEST
	//#define __LANG_ENG_USATEST_EXTERNAL
	//#define __LANG_ENG_IND_MAIN
	//#define __LANG_ENG_IND_TEST
//#define __LANG_GER
    //#define __LANG_GER_MAIN
	//#define __LANG_GER_TEST
	//#define __LANG_GER_NEXT_TEST
//#define __LANG_SPA
	//#define __LANG_SPA_CHIL
	//#define __LANG_SPA_CHILTEST
//#define __LANG_FRA
	//#define __LANG_FRA_FRA
	//#define __LANG_FRA_TEST
	//#define __LANG_FRA_NEXT_TEST
//#define __LANG_POR
	//#define __LANG_POR_BRA
	//#define __LANG_POR_BRATEST
//#define __LANG_VTN
	//#define __LANG_VTN_MAIN
	//#define __LANG_VTN_TEST
//#define __LANG_RUS
	//#define __LANG_RUS_MAIN
	//#define __LANG_RUS_TEST

#if	  defined(__TESTSERVER)		// 테섭
	#define	__VER 9
	#define __CURRENT_LANG LANG_KOR
	const int PATCH_VERSION = 55;
	#define WEB_FIRST_PAGE	"http://notice.flyff.com/news/news_list_dev.asp" //임시로 정섭 공지사항 링크 사용
	#define SERVER_ROOT		"down/aeonsoft/flyff/Patch/Test_ResClient"
	#define PATCHSEVER_URL	"aeonpatch.nowcdn.co.kr"
	#define	HOME_LINK		"http://www.flyff.com"
	#define VERSION_NAME	"Kor"
	#define LOGIN_LINK		"http://test.flyff.com"
	#define __LINK_PORTAL

#elif defined(__MAINSERVER)		// 외부 본섭
	#define	__VER 10
	#define __CURRENT_LANG LANG_KOR
	const int PATCH_VERSION = 41;
	#define WEB_FIRST_PAGE	"http://notice.flyff.com/news/news_list_dev.asp"
	#define SERVER_ROOT		"down/aeonsoft/flyff/Patch/ResClient"
	#define PATCHSEVER_URL	"aeonpatch.nowcdn.co.kr"
	#define	HOME_LINK		"http://www.flyff.com"
	#define VERSION_NAME	"Kor"
	#define LOGIN_LINK		"http://www.flyff.com"
	#define __LINK_PORTAL

#elif defined(__LANG_JAP)		// 일본
	#if defined(__JAPAN)
		#define	__VER 9
		#define __CURRENT_LANG LANG_JAP
		#define __HANGAME0307
		const int PATCH_VERSION = 37;
		#define WEB_FIRST_PAGE	"http://www.flyff.jp/in_client/info/list.asp?domain=flyff.jp"
		#define PATCHSEVER_URL	"cdn.game.excite.co.jp"
		#define SERVER_ROOT		"excite/flyff/patch"
		#define	HOME_LINK		"http://www.flyff.jp"
		#define VERSION_NAME	"Japan"
 	#elif defined(__JAPAN_TEST)
 		#define	__VER 9
 		#define __CURRENT_LANG LANG_JAP
 		#define __HANGAME0307
 		const int PATCH_VERSION = 37;
 		#define WEB_FIRST_PAGE	"http://www.flyff.jp/in_client/info/list.asp?domain=flyff.jp"
 		#define PATCHSEVER_URL	"210.148.99.30"
 		#define SERVER_ROOT		"ResClient"
 		#define	HOME_LINK		"http://www.flyff.jp"
 		#define VERSION_NAME	"Japan"
	#endif

#elif defined(__LANG_THAI)		// 태국
	#define	__VER 9
	#define __CURRENT_LANG LANG_THA
	#if defined( __LANG_THAI_MAIN )
		const int PATCH_VERSION = 41;
		#define WEB_FIRST_PAGE	"http://www.flyffonline.in.th/update_patch.html"
		#define SERVER_ROOT		"NEUROSPACE/RES_CLIENT_THA"
		#define PATCHSEVER_URL	"patch.flyffonline.in.th"		// THAI
		#define	HOME_LINK		"http://flyffonline.ini3.co.th"
		#define VERSION_NAME	"Thai"
	#elif defined( __LANG_THAI_TEST )
		const int PATCH_VERSION = 41;
		#define WEB_FIRST_PAGE	"http://www.flyffonline.in.th/update_patch.html"
		#define SERVER_ROOT		"NeuroSpace/RESCLIENT"
		#define PATCHSEVER_URL	"flyfftest.flyffonline.in.th"	// TEST_THAI
		#define	HOME_LINK		"http://flyffonline.ini3.co.th"
		#define VERSION_NAME	"Thai"
	#endif

#elif defined(__LANG_TAIWAN)
	#define __CURRENT_LANG LANG_TWN

	#if defined(__LANG_TAIWAN_MAIN)				// 대만 정섭
		#define __CURRENT_CNTRY CNTRY_TWN
		#define	__VER 12
		const int PATCH_VERSION = 26;
		#define SERVER_ROOT         "Flyff/Neurospace/Resclient"
		#define PATCHSEVER_URL      "patch.omg.com.tw"
		#define WEB_FIRST_PAGE      "http://www.omg.com.tw/fff"
		#define HOME_LINK           "http://www.omg.com.tw/"
		#define VERSION_NAME	    "Taiwan"
	#elif defined(__LANG_TAIWAN_TEST)			// 대만 테섭
		#define __CURRENT_CNTRY CNTRY_TWN
		#define	__VER 12
		const int PATCH_VERSION = 26;
		#define SERVER_ROOT         "Flyff/Neurospace/Resclient"
		#define PATCHSEVER_URL      "testpatch.omg.com.tw"
		#define WEB_FIRST_PAGE      "http://www.omg.com.tw/fff"
		#define HOME_LINK           "http://www.omg.com.tw/"
		#define VERSION_NAME	    "Taiwan"
	#elif defined(__LANG_TAIWAN_HONGKONG)		// 홍콩
		#define __CURRENT_CNTRY CNTRY_HK
		#define	__VER 9
		const int PATCH_VERSION = 29;
		#define SERVER_ROOT         "Flyff/Neurospace/Resclient"
		#define PATCHSEVER_URL      "203.174.49.230"
		#define WEB_FIRST_PAGE      "http://flyff.urgame.com.hk/notice.php"
		#define HOME_LINK           "http://flyff.urgame.com.hk"
		#define VERSION_NAME	    "Hongkong"
	#elif defined(__LANG_TAIWAN_HONGKONG_TEST)	// 홍콩 테섭
		#define __CURRENT_CNTRY CNTRY_HK
		#define	__VER 9
		const int PATCH_VERSION = 29;
		#define SERVER_ROOT         "Flyff/Neurospace/Resclient"
		#define PATCHSEVER_URL      "202.64.64.172"
		#define WEB_FIRST_PAGE      "http://flyff.urgame.com.hk/notice.php"
		#define HOME_LINK           "http://flyff.urgame.com.hk"
		#define VERSION_NAME	    "Hongkong"
	#endif

#elif defined(__LANG_ENG)
	#define __CURRENT_LANG LANG_ENG

	#if defined(__LANG_ENG_PHP)
		#define __COUNTRY CNTRY_PHI
		#define	__VER 14
		const int PATCH_VERSION = 35;  
		#define	WEB_FIRST_PAGE	"http://flyff.levelupgames.ph/news/flyffnews"
		#define	SERVER_ROOT		"NeuroSpace/VERSION6"
		#define	PATCHSEVER_URL	"patch.flyff.com.ph"
		#define	HOME_LINK		"http://flyff.levelupgames.ph"
		#define VERSION_NAME	""
	#elif defined(__LANG_ENG_PHPTEST)
		#define __COUNTRY CNTRY_PHI
		#define	__VER 14
		const int PATCH_VERSION = 35;  
		#define WEB_FIRST_PAGE  "http://flyff.levelupgames.ph/news/flyffnews"
		#define	SERVER_ROOT		"NeuroSpace/RESCLIENT_TEST"
		#define PATCHSEVER_URL  "flyfftest.flyff.com.ph"
		#define HOME_LINK       "http://flyff.levelupgames.ph"
		#define VERSION_NAME	""
	#elif defined(__LANG_ENG_USA)
		#define __COUNTRY CNTRY_USA
		#define	__VER 15
		const int PATCH_VERSION = 10;
		#define WEB_FIRST_PAGE  "http://www.tritiumflyff.com/news/"
		#define SERVER_ROOT     "Secret/RELEASE"
		#define PATCHSEVER_URL  "patch.tritiumflyff.com"
		#define HOME_LINK       "http://www.tritiumflyff.com"
		#define VERSION_NAME	""
	#elif defined(__LANG_ENG_USATEST)
		#define __COUNTRY CNTRY_USA
		#define	__VER 9
		const int PATCH_VERSION = 34;
		#define WEB_FIRST_PAGE  "http://flyffduy.gpotato.com/news/"
		#define SERVER_ROOT     "NeuroSpace/RESCLIENT_TEST"
		#define PATCHSEVER_URL  "flyfftest.gpotato.com"
		#define HOME_LINK       "http://flyff.gpotato.com/"
		#define VERSION_NAME	""
	#elif defined(__LANG_ENG_USATEST_EXTERNAL)
		#define __COUNTRY CNTRY_USA
		#define	__VER 9
		const int PATCH_VERSION = 34;
		#define WEB_FIRST_PAGE  "http://flyff.gpotato.com/news/index_test.html"
		#define SERVER_ROOT     "NeuroSpace/RESCLIENT_TEST"
		#define PATCHSEVER_URL  "204.2.134.202"
		#define HOME_LINK       "http://flyff.gpotato.com/"
		#define VERSION_NAME	""
	#elif defined(__LANG_ENG_IND_MAIN)
		#define __COUNTRY CNTRY_IND
		#define	__VER 9
		const int PATCH_VERSION = 2;
		#define WEB_FIRST_PAGE  ""
		#define SERVER_ROOT     "Neurospace/ResClient"
		#define PATCHSEVER_URL  "220.226.181.109"
		#define HOME_LINK       ""
		#define VERSION_NAME	""
	#elif defined(__LANG_ENG_IND_TEST)
		#define __COUNTRY CNTRY_IND
		#define	__VER 9
		const int PATCH_VERSION = 2;
		#define WEB_FIRST_PAGE  ""
		#define SERVER_ROOT     "Neurospace/ResClient"
		#define PATCHSEVER_URL  "220.226.181.109"
		#define HOME_LINK       ""
		#define VERSION_NAME	""
	#endif

#elif defined(__LANG_GER)		// 독일
	#if defined(__LANG_GER_MAIN)
		#define	__VER 12
		#define __CURRENT_LANG LANG_GER
		const int PATCH_VERSION = 32;
		#define WEB_FIRST_PAGE      "http://de.flyff.gpotato.eu/Game/Launcher/" //"http://flyff.gpotato.eu/news"
		#define SERVER_ROOT         "FlyffDE/RESCLIENT"
		#define PATCHSEVER_URL      "193.164.131.118" //"flyffserv.gpotato.eu"
		#define HOME_LINK           "http://fly.tbn.ms"
		#define VERSION_NAME	    ""
	#elif defined(__LANG_GER_TEST)
		#define	__VER 12		//Image 배경이 검은색이라 Text색상 변경하기 위해 12차 버전으로 구분(독일, 프랑스)
		#define __CURRENT_LANG LANG_GER
		const int PATCH_VERSION = 32;
		#define WEB_FIRST_PAGE      "http://de.flyff.gpotato.eu/Game/Launcher/" //"http://flyff.gpotato.eu/news"
		#define SERVER_ROOT         "FlyffDE/RESCLIENT_TEST"
		#define PATCHSEVER_URL      "84.203.140.29"
		#define HOME_LINK           "http://flyff.gpotato.eu"
		#define VERSION_NAME	    ""
	#elif defined(__LANG_GER_NEXT_TEST)
		#define	__VER 12		//Image 배경이 검은색이라 Text색상 변경하기 위해 12차 버전으로 구분(독일, 프랑스)
		#define __CURRENT_LANG LANG_GER
		const int PATCH_VERSION = 32;
		#define WEB_FIRST_PAGE      "http://de.flyff.gpotato.eu/Game/Launcher/" //"http://flyff.gpotato.eu/news"
		#define SERVER_ROOT         "FlyffDE/RESCLIENT_TEST"
		#define PATCHSEVER_URL      "84.203.140.30"
		#define HOME_LINK           "http://flyff.gpotato.eu"
		#define VERSION_NAME	    ""
	#endif

#elif defined(__LANG_SPA)		// 칠레
	#define	__VER 9
	#define __CURRENT_LANG LANG_SPA

	#if defined(__LANG_SPA_CHIL)
		const int PATCH_VERSION = 15;
		#define	WEB_FIRST_PAGE	"http://flyff.es.gpotato.com/news/"
		#define	SERVER_ROOT		"NeuroSpace/ResClient"
		#define	PATCHSEVER_URL	"flyff-es-patch.gpotato.com" //"http://flyff-ftp.zoomby.net" //"200.74.164.27"
		#define	HOME_LINK		"http://flyff.es.gpotato.com"
		#define VERSION_NAME	""
	#elif defined(__LANG_SPA_CHILTEST)
		const int PATCH_VERSION = 15;
		#define	WEB_FIRST_PAGE	"http://flyff.es.gpotato.com/news/"
		#define	SERVER_ROOT		"Neurospace/ResClient"
		#define	PATCHSEVER_URL	"204.2.134.13"
		#define	HOME_LINK		"http://flyff.es.gpotato.com"
		#define VERSION_NAME	""
	#endif

#elif defined(__LANG_FRA)		// 프랑스
	#define __CURRENT_LANG LANG_FRA

	#if defined(__LANG_FRA_FRA) //프랑스 -> BetaPatchClient.rc에서 버튼이미지 수동으로 풀어야 함.
		#define	__VER 12		//Image 배경이 검은색이라 Text색상 변경하기 위해 12차 버전으로 구분(독일, 프랑스)
		const int PATCH_VERSION = 25;
		#define	WEB_FIRST_PAGE	"http://fr.flyff.gpotato.eu/Game/Launcher/"
		#define	SERVER_ROOT		"FlyffFR/RESCLIENT"
		#define	PATCHSEVER_URL	"patch.flyff.gpotato.eu" //"flyffserv.gpotato.eu"
		#define	HOME_LINK		"http://flyff.gpotato.eu"
		#define VERSION_NAME	""
	#elif defined(__LANG_FRA_TEST)
		#define	__VER 12
		const int PATCH_VERSION = 25;  
		#define	WEB_FIRST_PAGE	"http://fr.flyff.gpotato.eu/Game/Launcher/"
		#define	SERVER_ROOT		"FlyffFR/RESCLIENT"
		#define	PATCHSEVER_URL	"84.203.140.31"
		#define	HOME_LINK		"http://flyff.gpotato.eu"
		#define VERSION_NAME	""
	#elif defined(__LANG_FRA_NEXT_TEST)
		#define	__VER 12
		const int PATCH_VERSION = 25;  
		#define	WEB_FIRST_PAGE	"http://fr.flyff.gpotato.eu/Game/Launcher/"
		#define	SERVER_ROOT		"FlyffFR/RESCLIENT"
		#define	PATCHSEVER_URL	"84.203.140.34"
		#define	HOME_LINK		"http://flyff.gpotato.eu"
		#define VERSION_NAME	""
	#endif

#elif defined(__LANG_POR)		// 브라질
	#define	__VER 12
	#define __CURRENT_LANG LANG_POR

	#if defined(__LANG_POR_BRA)
		const int PATCH_VERSION = 16;
		#define	WEB_FIRST_PAGE	"http://flyff.gpotato.com.br/news/"
		#define	SERVER_ROOT		"NeuroSpace/RESCLIENT"
		#define	PATCHSEVER_URL	"flyff-down.gpotato.com.br"
		#define	HOME_LINK		"http://flyff.gpotato.com.br"
		#define VERSION_NAME	""
	#elif defined(__LANG_POR_BRATEST)
		const int PATCH_VERSION = 16;
		#define	WEB_FIRST_PAGE	"http://flyff.gpotato.com.br/news/"
		#define	SERVER_ROOT		"NeuroSpace/RESCLIENT_TEST"
		#define	PATCHSEVER_URL	"204.2.134.65"
		#define	HOME_LINK		"http://flyff.gpotato.com.br"
		#define VERSION_NAME	""
	#endif

#elif defined(__LANG_VTN)		// 베트남
	#define	__VER 12
	#define __CURRENT_LANG LANG_VTN

	#if defined(__LANG_VTN_MAIN)
		const int PATCH_VERSION = 3;
		#define	WEB_FIRST_PAGE	"http://patch.flyff.vn"
		#define	SERVER_ROOT		"Neurospace/resclient"
		#define	PATCHSEVER_URL	"update.flyff.vn"
		#define	HOME_LINK		"http://www.flyff.vn"
		#define VERSION_NAME	""
	#elif defined(__LANG_VTN_TEST)
		const int PATCH_VERSION = 3;
		#define	WEB_FIRST_PAGE	"http://patch.flyff.vn"
		#define	SERVER_ROOT		"Neurospace/resclient_test"
		#define	PATCHSEVER_URL	"update1.flyff.vn"
		#define	HOME_LINK		"http://www.flyff.vn"
		#define VERSION_NAME	""
	#endif

#elif defined(__LANG_RUS)		// 러시아
	#define	__VER 12
	#define __CURRENT_LANG LANG_RUS

	#if defined(__LANG_RUS_MAIN)
		const int PATCH_VERSION = 11;
		#define	WEB_FIRST_PAGE		"http://flyffgame.ru/client/news"
		#define	WEB_FIRST_PAGE_2	"http://flyff.mail.ru/client/news"
		#define	SERVER_ROOT			"Neurospace/ResClient"
		#define	PATCHSEVER_URL		"patch.flyffgame.ru"
		#define	HOME_LINK			"http://flyffgame.ru"
		#define HOME_LINK_2			"http://flyff.mail.ru"
		#define VERSION_NAME		""
	#elif defined(__LANG_RUS_TEST)
		const int PATCH_VERSION = 11;
		#define	WEB_FIRST_PAGE		"http://flyffgame.ru/client/news"
		#define	WEB_FIRST_PAGE_2	"http://flyff.mail.ru/client/news"
		#define	SERVER_ROOT			"Neurospace/ResClient"
		#define	PATCHSEVER_URL		"91.212.60.104"
		#define	HOME_LINK			"http://flyffgame.ru"
		#define HOME_LINK_2			"http://flyff.mail.ru"
		#define VERSION_NAME		""
	#endif

#else

	#error COMPILE TARGET MUST BE DEFINED.

#endif	// end - 서버종류별 define

#endif // VERSION_COMMON_H
