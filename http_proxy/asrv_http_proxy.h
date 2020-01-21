
/*!
	\brief	�������Http��������
*/
class ASrvHttpProxy : public ShmHttpApp
{
public:
	ASrvHttpProxy() {};
	~ASrvHttpProxy();
	
    /*!
    	\brief	���������ļ���ʼ��
    */
    int init(const char* fpath);

	void run();

protected:
	void rcvProc();
	void sndProc();

	void on_rcvmsg( const cppkafka::Message& msg );
	void on_rcvpkt( GuteCommPkt* pkt );

protected:
	boost::thread_group		_thdGrp;					//!< ���߳���
	GuteCommPktQue*			_rcvQue = nullptr;			//!< ���ն���
	GuteCommPktQue*			_sndQue = nullptr;			//!< ���Ͷ���
	
	KafkaReceiver*			_kakfRcver = nullptr;		
	cppkafka::Producer* 	_kafkaProducer = nullptr;
};

