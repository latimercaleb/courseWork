<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Registration.aspx.cs" Inherits="WebApplication1.Registration" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
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
         #Label3 {
            margin-right: 10px;
            margin-bottom: 10px;
        }
          #Label4 {
            margin-right: 10px;
            margin-bottom: 10px;
        }
           #Button1 {
            margin-right: 10px;
        }
    </style>
    <h1>Welcome to registration</h1>
    <h5>Please enter the following fields to register:</h5>
        <asp:Label ID="Label1" runat="server" Text="First Name"></asp:Label>
        <asp:TextBox ID="TextBox1" runat="server" ></asp:TextBox>
        <br />
         <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ErrorMessage="Please enter your first name" ControlToValidate="TextBox1" ForeColor="Red"></asp:RequiredFieldValidator>
        <br />
        <br />
        <asp:Label ID="Label2" runat="server" Text="Last Name"></asp:Label>
        <asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
         <br />
        <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ErrorMessage="Please enter your last name" ControlToValidate="TextBox2" ForeColor="Red"></asp:RequiredFieldValidator>
        <br />
        <br />
        <asp:Label ID="Label3" runat="server" Text="LoginID"></asp:Label>
        <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
         <br />
        <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ErrorMessage="Please enter your loginID" ControlToValidate="TextBox3" ForeColor="Red"></asp:RequiredFieldValidator>
        <br />
        <br />
        <asp:Label ID="Label4" runat="server" Text="Password"></asp:Label>
        <asp:TextBox ID="TextBox4" runat="server"></asp:TextBox>
         <br />
        <asp:RequiredFieldValidator ID="RequiredFieldValidator4" runat="server" ErrorMessage="Please enter your password" ControlToValidate="TextBox4" ForeColor="Red"></asp:RequiredFieldValidator>
        <br />
        <br />
        <asp:Button ID="Button1" runat="server" Text="Submit" OnClick="Button1_Click"/> 
        <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="Clear" />
        <br />
        <br />
        <br />
        <p>Or use the information already in the database from the table below</p>
        <asp:GridView ID="GridView1" runat="server" DataSourceID="messagesEntityDataSource" AutoGenerateColumns="False" DataKeyNames="Id">
            <Columns>
                <asp:BoundField DataField="FirstName" HeaderText="First" SortExpression="FirstName" />
                <asp:BoundField DataField="LastName" HeaderText="Last" SortExpression="LastName" />
                <asp:BoundField DataField="LoginID" HeaderText="Login" SortExpression="LoginID" />
                <asp:BoundField DataField="Password" HeaderText="Password" SortExpression="Password" />
            </Columns>
        </asp:GridView>
        <asp:EntityDataSource ID="messagesEntityDataSource" runat="server" ConnectionString="name=UserDBEntities" DefaultContainerName="UserDBEntities" EnableFlattening="False" EntitySetName="Users">
        </asp:EntityDataSource>
    </form>
</body>
</html>
