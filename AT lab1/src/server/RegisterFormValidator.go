package main

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

func (self *RegisterFormValidator) Check(user *SiteUser) RegisterResult {
  result := RegisterResult{
    status: UserValid,
  }
  if len(user.nickname) == 0 {
    result.status = UserInvalidNickname
    result.message = "nickname is empty"
  } else if len(user.email) == 0 {
    result.status = UserInvalidEmail
    result.message = "e-mail is empty"
  } else if len(user.password) == 0 {
    result.status = UserWeakPassword
    result.message = "password is empty"
  }
  return result
}
