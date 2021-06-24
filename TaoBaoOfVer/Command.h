#ifndef CommandH

#define CommandH

enum Command {
	Exit=0,
	LogIn=1,
	LogOut=2,
	SignIn=3,
	AddGood,
	ChangeGood,
	ChangeUserInfo,
	Shop,
	ShowGoods,
	End,
	Income,
	AskGoodsInfo,
	ChangeInfo,
	ShowInfo,
	ChooseGood,
	ShowOrder,
	ManageOrder,
	Target,
	ShowSoldOrder,
	PullSoldOrder,
	Discount
};

enum _ClientType {
	ConsumerUser,
	SellerUser,
	Visitor,
	HalfConsumer,
	HalfSeller
};



#endif // !CommandH
