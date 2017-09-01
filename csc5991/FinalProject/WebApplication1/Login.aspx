<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="WebApplication1.Login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Final Project Login</title>
</head>
<body>
    <style>
        h1{
            text-align: center;
            text-decoration: underline;
        }
        #Label1 {
            margin-right: 20px;
            margin-bottom: 10px;
        }
        #Label2 {
            margin-right: 10px;
            margin-bottom: 10px;
        }
       #Button1 {
           margin-right: 20px;
       }
    </style>
    <h1>Welcome to registration</h1>
    <h5>Please login to proceed:</h5>

    <form id="form1" runat="server">
        <asp:Label ID="Label1" runat="server" Text="LoginID"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
        <br />
        <br />
        <asp:Label ID="Label2" runat="server" Text="Password"></asp:Label>
        <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
        <br />
        <br />
        <asp:Button ID="Button1" runat="server" Text="Login" OnClick="Button1_Click" /> 
        <asp:Button ID="Button2" runat="server" Text="Register" OnClick="Button2_Click" CausesValidation="False" />
    </form>
</body>
</html>
