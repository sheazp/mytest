
ASrvHttpProxy::ASrvHttpProxy()
{
}

ASrvHttpProxy::~ASrvHttpProxy()
{
}

int ASrvHttpProxy:: init(const char* fpath);
{
	return 0;
}

void ASrvHttpProxy::run()
{
	setStateRunning();
	
	_thdGrp.create_thread( [this](){rcvProc();} );	

	_kakfRcver->setFnMsgDispatch( 
		[this](const cppkafka::Message& msg)
		{
			on_rcvmsg( msg );
		} );
	_thdGrp.create_thread(TRunFunctor<RunnableInterface>(*_kakfRcver));
	
	ShmHttpApp::run();
}

void ASrvHttpProxy::rcvProc()
{
    GuteCommPkt* pkt;
    for (; ; )
    {
        if (checkExitLoop())
            break;
		
		if ( _rcvQue )
		{
	        while ( pkt = _rcvQue->pop() )
	        {
	            on_rcvpkt( pkt );
	        }
	    }
	
		try {
			boost::this_thread::sleep_for(boost::chrono::milliseconds(_interval_ms));
		}
		catch (boost::thread_interrupted&)
		{
			gw_debug("%s caught an thread interrupt, exiting cleanly.\n", typeid(*this).name());
			break;
		}
    }
}

void ASrvHttpProxy::sndProc()
{
}

void ASrvHttpProxy::on_rcvpkt( GuteCommPkt* pkt )
{
	//to do, 格式转换，发送到kafka
}

void ASrvHttpProxy::on_rcvmsg( const cppkafka::Message& msg )
{
	//to do, 格式转换，发送到sndQue
}


