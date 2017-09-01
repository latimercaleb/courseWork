<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Main.aspx.cs" Inherits="WebApplication1.Main" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Final Project Main</title>
</head>
<body>
    <style>
        h1 {
            text-align: center;
            text-decoration: underline;
        }

        #Logout {
            margin-right: 10px;
        }
        
        #form1 {
            margin: 20px;
        }

    </style>
    <form id="form1" runat="server">
        <h1>Main</h1>
        <asp:Label ID="Welcome" runat="server" Text="Label"></asp:Label>
        <br />
        <asp:Button ID="Logout" runat="server" OnClick="Logout_Click" Text="Logout" />
        <asp:Button ID="Login" runat="server" OnClick="Login_Click" Text="Login" />
        <br />
        <asp:GridView ID="UserData" runat="server" OnSelectedIndexChanged="UserData_SelectedIndexChanged">
            <Columns>
                <asp:CommandField ShowSelectButton="True" SelectText="Drop Class" />
            </Columns>
        </asp:GridView>
        <asp:Label ID="ClassRegisterPrompt" runat="server" Text="Label"></asp:Label>
        <asp:LinkButton ID="Registration" runat="server" OnClick="Registration_Click">Click here</asp:LinkButton>
    </form>

</body>
</html>
