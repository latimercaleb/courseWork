<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Main.aspx.cs" Inherits="WebApplication1.Main" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <style>
        h1{
            text-align: center;
            text-decoration: underline;
        }
        #button1{
            margin-right: 10px;
        }
    </style>
    <form id="form1" runat="server">
        <h1>Main page</h1>
        <h5>You made it!</h5>
        <asp:Label ID="Label1" runat="server" Text="Label"></asp:Label>
        <p>
        <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Logout" />
        <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="Login" />
        </p>
    </form>
</body>
</html>
