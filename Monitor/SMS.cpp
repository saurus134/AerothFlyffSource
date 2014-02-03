// SMS.cpp: implementation of the CSMS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSMS::CSMS()
{

}

CSMS::~CSMS()
{

}

char* CSMS::getToken(char **p)
{
	char *p0=*p;

        while (1)
	                
		switch (**p)
		{ 
			case '\t': 
			case '\r': 
			case '\n': 
			case '\0': 
				
				if (p0==*p) return NULL;

				if (**p) {
					**p='\0';
					(*p)++;
				}; 
				
				return p0;
			default:
				(*p)++;
		};
}


char* CSMS::get_packet_info( char* szTranId, char* szTranPwd, char* szRcvNum, 
							char* szSendNum, char* szDate, char* szMsg, BOOL &bResult )
{
	CLIENT_DATA	client_data_info;
//	char	*tmp;
//	char *tTok;
	char *sendmsg;
	int total_data_len = 0;

//	sendmsg = malloc(190);
	sendmsg = new char[190];
	memset(sendmsg, 0, 190);

	client_data_info.tran_id = szTranId;
	if(client_data_info.tran_id == NULL)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_ID is NULL" );
		return sendmsg;
	}

	if(strlen(client_data_info.tran_id) > 20)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_ID > 20" );
		return sendmsg;	}


	client_data_info.tran_passwd = szTranPwd;
	if(client_data_info.tran_passwd == NULL)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_PASSWORD is NULL" );
		return sendmsg;
	}

	if(strlen(client_data_info.tran_passwd) > 20)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_PASSWORD > 20" );
		return sendmsg;
	}


	client_data_info.tran_phone = szRcvNum;
	if(client_data_info.tran_phone == NULL)
	{
		bResult = FALSE;
		strcpy( sendmsg, "Recieve PhoneNum is NULL" );
		return sendmsg;
	}

	if(strlen(client_data_info.tran_phone) > 15)
	{
		bResult = FALSE;
		strcpy( sendmsg, "Recieve PhoneNum > 15" );
		return sendmsg;
	}


	client_data_info.tran_callback = szSendNum;
	if(client_data_info.tran_callback == NULL)
	{
		bResult = FALSE;
		strcpy( sendmsg, "Send PhoneNum is NULL" );
		return sendmsg;
	}

	if(strlen(client_data_info.tran_callback) > 15)
	{
		bResult = FALSE;
		strcpy( sendmsg, "Send PhoneNum > 15" );
		return sendmsg;
	}


	client_data_info.tran_date = szDate;
	if(client_data_info.tran_date == NULL)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_DATE is NULL" );
		return sendmsg;
	}

	if(strlen(client_data_info.tran_date) > 19)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_DATE > 19" );
		return sendmsg;
	}


	client_data_info.tran_msg = szMsg;
	if(client_data_info.tran_msg == NULL)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_MESSAGE is NULL" );
		return sendmsg;
	}


	if(strlen(client_data_info.tran_msg) > 80)
	{
		bResult = FALSE;
		strcpy( sendmsg, "TRAN_MESSAGE > 80" );
		return sendmsg;
	}


	total_data_len = strlen(client_data_info.tran_id)+
		strlen(client_data_info.tran_passwd) + 
		strlen(client_data_info.tran_phone) + 
		strlen(client_data_info.tran_callback) + 
		strlen(client_data_info.tran_date) + 
		strlen(client_data_info.tran_msg) +1 ; 

	if(total_data_len > LIMIT_DATA_LEN)
	{
		bResult = FALSE;
		strcpy( sendmsg, "total_data_len > LIMIT_DATA_LEN" );
		return sendmsg;
	}

	sprintf(sendmsg, "%s,%d,%s,%s,%s,%s,%d,%s,%s\n",SMS_KEY,total_data_len,client_data_info.tran_id,client_data_info.tran_passwd,
		client_data_info.tran_phone,client_data_info.tran_callback,TRAN_STATUS,client_data_info.tran_date,client_data_info.tran_msg);

	bResult = TRUE;
	return sendmsg;
}


char* CSMS::SendMsg( char* szTranId, char* szTranPwd, char* szRcvNum, char* szSendNum, char* szDate, char* szMsg )
{
	struct hostent *hp;
	int n,sock, serv_len;
//	int t, clnt_len, msglen, sendmsglen;
	struct sockaddr_in serv_addr;
//	struct sockaddr_in clnt_addr;
	server_name = "sms.gabia.com";
	char* szRtnMsg = new char[256];
	BOOL bResult;

	clientmsg = get_packet_info( szTranId, szTranPwd, szRcvNum, szSendNum, szDate, szMsg, bResult );
	if( !bResult )
		return clientmsg;

	if((hp=gethostbyname(server_name)) == NULL)
	{
		strcpy( szRtnMsg, "gethostbyname() failed" );
		return szRtnMsg;
	}

	serv_len=sizeof(serv_addr);
	memset((char *)&serv_addr, '\0',serv_len);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORTNUM);
	memcpy((char *)&serv_addr.sin_addr, hp->h_addr, hp->h_length);

	if((sock=socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		strcpy( szRtnMsg, "Socket Error" );
		return szRtnMsg;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
	{
		strcpy( szRtnMsg, "Connect Error" );
		return szRtnMsg;
	}

	if( sendto(sock, clientmsg, strlen(clientmsg), 0,(struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) == -1 )
	{
		strcpy( szRtnMsg, "Send Error" );
		closesocket( sock );
		return szRtnMsg;
	}
  
	if((n=recv(sock, reply, MAXMSG, 0)) < 0)
	{
		strcpy( szRtnMsg, "Receive error" );
		closesocket( sock );
		return szRtnMsg;
	}
	else
	{
		sprintf( szRtnMsg, "send to server : %s", clientmsg );
		closesocket( sock );
		return szRtnMsg;
	}
	
}