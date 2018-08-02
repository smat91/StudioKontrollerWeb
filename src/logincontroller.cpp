#include "logincontroller.h"

LoginController::LoginController(QObject* parent)
    :HttpRequestHandler(parent) {
    // empty
}

void LoginController::service(HttpRequest &request, HttpResponse &response) {
    QByteArray username=request.getParameter("username");
    QByteArray password=request.getParameter("password");

    qDebug("username=%s",username.constData());
    qDebug("password=%s",password.constData());

    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    response.write("<html><body>");

    if (username=="test" && password=="hello") {
        response.write("Yes, correct");
    }
    else {
        response.write("<form method='POST' action='/login'>");
        if (!username.isEmpty()) {
            response.write("No, that was wrong!<br><br>");
        }
        response.write("Please log in:<br>");
        response.write("Name:  <input type='text' name='username'><br>");
        response.write("Password: <input type='password' name='password'><br>");
        response.write("<input type='submit'>");
        response.write("</form");
    }

    response.write("</body></html>",true);
}
