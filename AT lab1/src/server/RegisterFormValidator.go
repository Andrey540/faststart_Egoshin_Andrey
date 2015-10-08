package main

import (
	"regexp"
	"strings"
)


const (
  UserValid = iota
  UserInvalidNickname
  UserInvalidEmail
  UserWeakPassword
  UserPasswordMismatch
)

type RegisterResult struct {
  status int32
  message string
}

type RegisterFormValidator struct {
}

func (self *RegisterFormValidator) ValidateNickname(user *SiteUser) RegisterResult {
	result := RegisterResult{
    status: UserValid,
  }
  re := regexp.MustCompile(`^[a-zA-Z0-9_]+$`)
  if len(user.nickname) < 3 {
    result.status = UserInvalidNickname
    result.message = "nickname invalid length"
  } else if len(re.FindString(user.nickname)) == 0 {
    result.status = UserInvalidNickname
    result.message = "nickname must contains only letters and digits"
  } 
  return result
}

func (self *RegisterFormValidator) ValidateEmail(user *SiteUser) RegisterResult {
	result := RegisterResult{
    status: UserValid,
  }

  separatorPosition := strings.Index(user.email, "@")
  if len(user.email) == 0 {
    result.status = UserInvalidEmail
    result.message = "email is empty"
  } else if user.email[0] == '@' || user.email[0] == ' ' || user.email[0] == '_' {
    result.status = UserInvalidEmail
    result.message = "invalid login"
  } else if separatorPosition < 0 || separatorPosition != strings.LastIndex(user.email, "@") {
	result.status = UserInvalidEmail
    result.message = "not enougth @"
  } else if separatorPosition == len(user.email) {
	result.status = UserInvalidEmail
    result.message = "empty domain name"
  } else if (((strings.LastIndex(user.email, "gmail.com") < 0) || (separatorPosition + 10 != len(user.email))) &&
	    	 ((strings.LastIndex(user.email, "yandex.com") < 0) || (separatorPosition + 11 != len(user.email))) &&
		     ((strings.LastIndex(user.email, "mail.com") < 0) || (separatorPosition + 9 != len(user.email))) &&
		     ((strings.LastIndex(user.email, "mail.ru") < 0) || (separatorPosition + 8 != len(user.email)))) {
	result.status = UserInvalidEmail
    result.message = "invalid domain"
  }

  return result
}

func (self *RegisterFormValidator) ValidatePassword(user *SiteUser) RegisterResult {
	result := RegisterResult{
    status: UserValid,
  }

  regexpLettersAndDigits := regexp.MustCompile(`^[а-яА-Яa-zA-Z0-9]+$`)
  regexpLetters := regexp.MustCompile(`[а-яА-Яa-zA-Z]+`)
  regexpDigits := regexp.MustCompile(`[0-9]+`)
  if len(user.password) < 5 {
    result.status = UserWeakPassword
    result.message = "password invalid length"
  } else if len(regexpLettersAndDigits.FindString(user.password)) == 0 {
    result.status = UserWeakPassword
    result.message = "password must contains only letters and digits"
  } else if len(regexpLetters.FindString(user.password)) == 0 {
    result.status = UserWeakPassword
    result.message = "password must contains letters"
  } else if len(regexpDigits.FindString(user.password)) == 0 {
    result.status = UserWeakPassword
    result.message = "password must contains digits"
  } else if user.password != user.passwordRepeat {
    result.status = UserPasswordMismatch
    result.message = "passwords are not equal"
  } 

  return result
}

func (self *RegisterFormValidator) Check(user *SiteUser) RegisterResult {
  checkResult := self.ValidateNickname(user)
  if checkResult.status != UserValid {
	return checkResult
  }
  checkResult = self.ValidateEmail(user)
  if checkResult.status != UserValid {
	return checkResult
  }
  checkResult = self.ValidatePassword(user)
  if checkResult.status != UserValid {
	return checkResult
  }
  return checkResult
}
