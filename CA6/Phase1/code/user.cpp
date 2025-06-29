#include "user.hpp"

User::User(std::string n,std::string i,std::string p)
{
	name = n;
	id = i;
	password = p;
	logged_in = false;
	num_of_posts_history = 0;
}

User::User(std::string n,std::string i,std::string m,std::string m_i,std::string p)
{
	name = n;
	id = i;
	major_id = m_i;
	major = m;
	password = p;
	logged_in = false;
	num_of_posts_history = 0;
}

bool User::is_Logged_In()
{
	return logged_in;
}

bool User::is_Valid_Id(std::string i)
{
	if(id == i)
		return true;
	return false;
}

bool User::is_Valid_Password(std::string p)
{
	if(password == p)
		return true;
	return false;
}

void User::Login()
{
	logged_in = true;
}

void User::Logout()
{
	logged_in =false;
}

void User::Add_Post(UT_Post *post)
{	
	post->id = std::to_string(num_of_posts_history +1);
	posts.push_back(post);
	Send_Notification(NOTIFICATION_1);
	num_of_posts_history++;
}

void User::Connect(User *target)
{
	for(int i=0 ; i<connection_list.size() ; i++)
	{
		if(connection_list[i] == target)
			throw AvailabilityException(ERROR_1);
	}
	connection_list.push_back(target);
}

bool User::Permision_Check(std::string cmd)
{
	for(int i=0 ; i<valid_cmds.size(); i++)
	{
		if(cmd == valid_cmds[i])
			return true;
	}
	return false;
}



std::string User::get_Type()
{
	return user_type;
}

std::string User::get_Major_Id()
{
	return major_id;
}

std::string User::get_Name()
{
	return name;
}

void User::Sort_Posts()
{
	UT_Post *temp;
	for(int i=0 ; i<posts.size() ; i++)
	{
		for(int j=0 ; j<posts.size() -1 ; j++)
		{
			if(posts[j]->id < posts[j+1]->id)
			{
				temp = posts[j];
				posts[j] = posts[j+1];
				posts[j+1] = temp;
			}
		}
	}
}

std::string User::get_Post(std::string post_id)
{
	std::ostringstream S;
	UT_Post *post;
	bool id_validation = false;

	for(int i=0 ; i<posts.size() ; i++)
	{
		if(posts[i]->id == post_id)
		{
			id_validation = true;
			post = posts[i];
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(ERROR_2);
	S << this->get_Info();
	S << post->id << SPACE_CHAR << post->title <<SPACE_CHAR << post->message << std::endl;
	return S.str();
}

void User::Send_Notification(std::string notice_text)
{
	for(int i=0 ; i<connection_list.size() ; i++)
	{	
		connection_list[i]->Recieve_Notification(new Notification{id,name,notice_text});
	}
}

void User::Recieve_Notification(Notification* notif)
{
	notifications.push_back(notif);
}

std::string User::get_Notifications()
{
	std::ostringstream S;

	if(notifications.size() == 0)
		throw AvailabilityException(ERROR_4);

	for(int i= notifications.size() - 1 ; i>=0 ; i--)
	{
		S << notifications[i]->user_id << SPACE_CHAR << notifications[i]->name << NAME_POST_SEPRATOR  << SPACE_CHAR << notifications[i]->notice << std::endl;
		delete notifications[i];
	}

	notifications.clear();
	
	return S.str();
}

void User::Delete_Post(std::string post_id)
{
	bool id_validation = false;
	for(int i=0 ; i<posts.size() ; i++)
	{
		if(posts[i]->id == post_id)
		{
			id_validation = true;
			delete posts[i];
			posts.erase(posts.begin() + i);
			break;
		}
	}
	if(!id_validation)
		throw AvailabilityException(ERROR_2);
}


std::string User::get_Id()
{
	return id;
}

void User::Free_Allocated_Memory()
{
	for(int i=0 ; i<posts.size() ; i++)
		delete posts[i];
	
	for(int i=0 ; i<notifications.size() ; i++)
		delete notifications[i];
}	
