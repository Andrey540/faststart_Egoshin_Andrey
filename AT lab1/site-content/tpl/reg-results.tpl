<!DOCTYPE html>
<html lang="ru">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="/css/bootstrap.min.css">
    <link rel="stylesheet" href="/css/bootstrap-theme.min.css">
  </head>
  <body>
    <div class="container">
      <div class="row">
        <h2>
          {{.title}}
        </h2>
      </div>
      <div class="row">
        <a href="/form">&lt;- Back to form</a>
      </div>
      <div class="row">
        <p>Nickname: {{.userNickname}}</p>
        <p>Email: {{.userEmail}}</p>
      </div>
    </div>
  </body>
</html>
