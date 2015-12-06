package main

import "github.com/gin-gonic/gin"
import "net/http"

func RenderRegisterForm(ctx *gin.Context, result *RegisterResult, user *SiteUser) {
  tplData := gin.H{
    "title": "Automata Theory - Lab 1, form validation",
    "alertMessage": "",
    "showAlertName": false,
    "showAlertEmail": false,
    "showAlertPassword": false,
  }
  if result != nil && result.status != UserValid {
    tplData["alertMessage"] = result.message
    switch result.status {
    case UserInvalidNickname:
      tplData["showAlertName"] = true
    case UserInvalidEmail:
      tplData["showAlertEmail"] = true
    case UserWeakPassword:
	  tplData["showAlertPassword"] = true
	case UserPasswordMismatch:
      tplData["showAlertPassword"] = true
    }
	
	if user != nil {
	  tplData["userNickname"] = user.nickname
	  tplData["userEmail"]    = user.email
	  tplData["userPassword"] = user.password
	}
  }
  ctx.HTML(http.StatusOK, "reg-form.tpl", tplData)
}

func RenderLivePage(ctx *gin.Context) {
  tplData := gin.H{
    "title": "Automata Theory - Lab 2",
  }
  ctx.HTML(http.StatusOK, "live.tpl", tplData)
}

func RenderCalcForm(ctx *gin.Context, result float64, alert string) {
  tplData := gin.H{
    "title": "Automata Theory - Lab 3",
	"result": result,
	"showAlertExpression": len(alert) > 0,
	"alertMessage": alert,
  }
  ctx.HTML(http.StatusOK, "calc.tpl", tplData)
}

func RenderUserPage(ctx *gin.Context, user *SiteUser) {
  ctx.HTML(http.StatusOK, "reg-results.tpl", gin.H{
    "title": "Automata Theory - Lab 1, form validation",
    "userNickname": user.nickname,
    "userEmail": user.email,
  })
}

func main() {
  lexer := new(Lexer)
  lexer.parseTokens("  1 + 3 4534 78")


  cache := NewSiteUsersCache()
  validator := new(RegisterFormValidator)

  router := gin.Default()
  router.Static("/css", "../site-content/css")
  router.Static("/js", "../site-content/js")
  router.LoadHTMLGlob("../site-content/tpl/*.tpl")
  router.GET("/form", func(ctx *gin.Context) {
    RenderRegisterForm(ctx, nil, nil)
  })  
  router.POST("/form", func(ctx *gin.Context) {
    user := &SiteUser{
      nickname: ctx.PostForm("userNickname"),
      email: ctx.PostForm("userEmail"),
      password: ctx.PostForm("userPassword"),
	  passwordRepeat: ctx.PostForm("userPasswordRepeat"),
    }

    checkResult := validator.Check(user)
    if checkResult.status == UserValid {
      cache.AddUser(user)
      RenderUserPage(ctx, user)
    } else {
      RenderRegisterForm(ctx, &checkResult, user)
    }
  })
  router.GET("/live", func(ctx *gin.Context) {
    RenderLivePage(ctx)
  })
  router.GET("/calc", func(ctx *gin.Context) {
    RenderCalcForm(ctx, 0, "")
  })
  router.POST("/calc", func(ctx *gin.Context) {
    expression:= ctx.PostForm("expression")
	
	calculator := new(Calculator)
	result, alert := calculator.calculate(expression);

    RenderCalcForm(ctx, result, alert)
  })
  router.Run(":8080")  
}
