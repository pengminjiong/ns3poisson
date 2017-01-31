
#include "carserver.h"
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/packet.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/ndn-app-face.h"
#include "ns3/ndn-interest.h"
#include "ns3/ndn-data.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndn-fib.h"
#include "ns3/random-variable.h"

NS_LOG_COMPONENT_DEFINE ("CarServerApp1");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CarServerApp1);
Ptr<const ndn::Interest> *interestp1[10];
TypeId
CarServerApp1::GetTypeId ()
{
  static TypeId tid = TypeId ("CarServerApp1")
    .SetParent<ndn::App> ()
    .AddConstructor<CarServerApp1> ()
    ;
  return tid;
}

void
CarServerApp1::StartApplication ()
{
  ndn::App::StartApplication ();

  Ptr<ndn::Name> prefix = Create<ndn::Name> (); 
  prefix->append ("prefix"); 
  prefix->append ("sub"); 


  Ptr<ndn::Fib> fib = GetNode ()->GetObject<ndn::Fib> ();

  Ptr<ndn::fib::Entry> fibEntry = fib->Add (*prefix, m_face, 0);

}

void
CarServerApp1::StopApplication ()
{
  ndn::App::StopApplication ();
}

void
CarServerApp1::SendInterest ()
{//  this in empty because this applicaiton only works as a publisher , keep this fuction for future dynamcial controll
}

void
CarServerApp1::OnInterest (Ptr<const ndn::Interest> interest)
{
ndn::App::OnInterest (interest);

  NS_LOG_DEBUG ("Received Interest packet for " << interest->GetName ());


  Ptr<ndn::Data> data = Create<ndn::Data> (Create<Packet> (1024));
  data->SetName (Create<ndn::Name> (interest->GetName ())); // data will have the same name as Interests

  NS_LOG_DEBUG ("Sending Data packet for " << data->GetName ());  

  m_transmittedDatas (data, this, m_face);

  m_face->ReceiveData (data); 

}


void
CarServerApp1::OnData (Ptr<const ndn::Data> contentObject)
{//  this in empty because this applicaiton only works as a publisher , keep this fuction for future dynamcial controll
}

} 
