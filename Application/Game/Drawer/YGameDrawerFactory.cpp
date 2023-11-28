//#include "YGameDrawerFactory.h"
//#include "PlayerDrawer.h"
//#include "HorseDrawer.h"
//#include "SlimeDrawer.h"
//#include "CoinDrawer.h"
////#include "MagnetDrawer.h"
////#include "LifeDrawer.h"
//#include "DefaultDrawer.h"
//
//using YGame::YGameDrawerFactory;
//using YGame::BaseDrawer;
//
//const std::string YGameDrawerFactory::Player_	 = "PLAYER";
//const std::string YGameDrawerFactory::Horse_	 = "HORSE";
//const std::string YGameDrawerFactory::Slime_	 = "SLIME";
//const std::string YGameDrawerFactory::Coin_		 = "COIN";
//const std::string YGameDrawerFactory::Magnet_	 = "MAGNET";
//const std::string YGameDrawerFactory::Life_		 = "LIFE";
//const std::string YGameDrawerFactory::Default_	 = "DEFAULT";
//
//std::unique_ptr<BaseDrawer> YGameDrawerFactory::CreateDrawer(
//	const std::string& drawerName, Transform* pParent, const size_t drawPriority)
//{
//	// 次のシーンを生成
//	std::unique_ptr<BaseDrawer> newDrawer;
//
//	if (drawerName == Player_)	{ newDrawer = PlayerDrawer::Create(pParent, drawPriority); }
//	if (drawerName == Horse_)	{ newDrawer = HorseDrawer::Create(pParent, drawPriority); }
//	if (drawerName == Slime_)	{ newDrawer = SlimeDrawer::Create(pParent, drawPriority); }
//	if (drawerName == Coin_)	{ newDrawer = CoinDrawer::Create(pParent, drawPriority); }
//	//if (drawerName == Magnet_)	{ newDrawer = MagnetDrawer::Create(pParent, drawPriority); }
//	//if (drawerName == Life_)	{ newDrawer = LifeDrawer::Create(pParent, drawPriority); }
//	if (drawerName == Default_)	{ newDrawer = DefaultDrawer::Create(pParent, drawPriority); }
//
//	return std::move(newDrawer);
//}
