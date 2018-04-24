
#include<iostream>

#include "institute_member.h"

/////////////////////////////////////////////////////////////////////////////////////class function

Institute_member::Institute_member(){}

Institute_member::Institute_member(std::string _id){
	instituteId = _id;
}

std::string Institute_member::getInstituteId (){
	return instituteId;
}

void Institute_member::setInstituteId (std::string _instituteId){
	instituteId = _instituteId;
}
