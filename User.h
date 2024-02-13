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

};