<!DOCTYPE html>
<html lang="ru">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="/css/bootstrap.min.css">
    <link rel="stylesheet" href="/css/bootstrap-theme.min.css">
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js"></script>
  </head>
  <body>
    <div class="container">
      <div class="row">
        <h2>
          {{.title}}
        </h2>
      </div>
      <div class="row">
        <form name="calc" action="/calc" method="POST">
          <div class="form-group">
            <label for="expression">Expression</label>
            {{if .showAlertExpression}}
              <div class="alert alert-danger" role="alert">{{.alertMessage}}</div>
            {{end}}
            <input type="text" class="form-control" id="expression" placeholder="Your Expression" name="expression">
          </div>
          <!--<div class="checkbox">
            <label>
              <input type="checkbox">Don't remember me
            </label>
          </div>-->
          <button type="submit" class="btn btn-default">Submit</button>
        </form>
		<div class="form-group">
          <label for="result">Result</label>
          <input type="input" value="{{.result}}" class="form-control" id="result"name="result">
        </div>
      </div>
    </div>
  </body>
</html>
