#ifndef USER_H
#define USER_H
#endif // !USER_H

//The User class represents an account on the system
class User 
{
	public:

		string name;
		string type;
		float credit;

		User() {
			name = "";
			type = "";
			credit = 0.0;
		}

		User(string userName, string userType, float userCredit) {
			name = userName;
			type = userType;
			credit = userCredit;
		}

		void ClearUser()
		{
			name = "";
			type = "";
			credit = 0.0;
		}

		/*
		/// Given a user type code, returns the descriptive name of the account type.
		string getUserTypeVerbose(string type)
		{
			if (type == "AA") { return "admin"; }
			if (type == "FS") { return "full standard"; }
			if (type == "BS") { return "buy standard"; }
			if (type == "SS") { return "sell standard"; }
		}*/
};