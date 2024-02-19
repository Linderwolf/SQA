#ifndef USER_H
#define USER_H
#endif // !USER_H

//The User class represents an account on the system
class User 
{
	public:

		string name;	// The username of a User
		string type;	// The type of account, which determines permissions
		float credit;	// The User's account balance

		// Default Constructor
		User() {
			name = "               ";
			type = "";
			credit = 0.0;
		}

		// Parameterized Constructor
		User(string userName, string userType, float userCredit) {
			name = userName;
			type = userType;
			credit = userCredit;
		}
};