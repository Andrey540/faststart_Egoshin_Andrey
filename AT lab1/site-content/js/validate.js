function validateNickname()
{
	var nickname = $('#exampleInputNickname').val();
	if ((nickname.length < 3) ||
	    (nickname.match(/^[a-zA-Z0-9_]+$/) == null))
	{
		return false;
	}
	return true;
}

function validateEmail()
{
	var email = $('#exampleInputEmail').val();
	var separatorPosition = email.indexOf('@');
	if ((!email.length) ||
		((email[0] == '@') || (email[0] == ' ') || (email[0] == '_')) ||
		((!separatorPosition) || (email.indexOf('@', separatorPosition + 1) >= 0)) ||
		(separatorPosition == email.length) ||
		(((!email.indexOf('gmail.com', separatorPosition + 1)) || (separatorPosition + 10 != email.length)) &&
		 ((!email.indexOf('yandex.com', separatorPosition + 1)) || (separatorPosition + 11 != email.length)) &&
		 ((!email.indexOf('yandex.com', separatorPosition + 1)) || (separatorPosition + 11 != email.length)) &&
		 ((!email.indexOf('mail.com', separatorPosition + 1)) || (separatorPosition + 9 != email.length)) &&
		 ((!email.indexOf('mail.ru', separatorPosition + 1)) || (separatorPosition + 8 != email.length))))
	{
		return false;
	}
	return true;
}

function validatePassword()
{
	var password1 = $('#exampleInputPassword1').val();
	var password2 = $('#exampleInputPassword2').val();
	if ((password1.length < 5) ||
	    (password1.match(/^[à-ÿÀ-ßa-zA-Z0-9]+$/) == null) || 
		(password1.match(/[à-ÿÀ-ßa-zA-Z]+/) == null) || 
		(password1.match(/[0-9]+/) == null) ||
		(password1 != password2))
	{
		return false;
	}
	return true;
}

window.onload = function()
{
	$("form[name='register_user']").submit(function(){
		 return validateNickname() &&
				validateEmail() &&
				validatePassword();
	});
}