
/*!
	\brief	接入服务Http代理处理类
*/
class ASrvHttpProxy : public ShmHttpApp
{
public:
	ASrvHttpProxy() {};
	~ASrvHttpProxy();
	
    /*!
    	\brief	根据配置文件初始化
    */
    int init(const char* fpath);

	void run();

protected:
	void rcvProc();
	void sndProc();

	void on_rcvmsg( const cppkafka::Message& msg );
	void on_rcvpkt( GuteCommPkt* pkt );

protected:
	boost::thread_group		_thdGrp;					//!< 子线程组
	GuteCommPktQue*			_rcvQue = nullptr;			//!< 接收队列
	GuteCommPktQue*			_sndQue = nullptr;			//!< 发送队列
	
	KafkaReceiver*			_kakfRcver = nullptr;		
	cppkafka::Producer* 	_kafkaProducer = nullptr;
};

