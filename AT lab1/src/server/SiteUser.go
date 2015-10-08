package main

type SiteUser struct {
  nickname string
  email string
  password string
  passwordRepeat string
}

type SiteUsersCache struct {
  users map[string]*SiteUser
}

func NewSiteUsersCache() *SiteUsersCache {
  self := new(SiteUsersCache)
  self.users = make(map[string]*SiteUser)
  return self
}

func (self *SiteUsersCache) AddUser(user *SiteUser) {
  if user != nil {
    self.users[user.email] = user
  }
}

func (self *SiteUsersCache) GetUserByEmail(email string) *SiteUser {
  return self.users[email]
}
