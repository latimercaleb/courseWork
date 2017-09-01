<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ClassSelect.aspx.cs" Inherits="WebApplication1.ClassSelect" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Final Project Class Select</title>
</head>
<body>
    <style>
        h1 {
            text-align: center;
            text-decoration: underline;
        }
       #Logout, #Register {
           margin-right: 20px;
       }
    </style>
    <form id="classSelectForm" runat="server">
         <h1>Class Selection</h1>
         <asp:Button ID="Logout" runat="server" Text="Logout" OnClick="Logout_Click" />
         <asp:button ID="Login" runat="server" Text="Login" OnClick="Login_Click" />
        <br /><br />
         <asp:Label ID="Welcome" runat="server" Text="Label"></asp:Label>
        <br />
    <asp:Label id="instructions" runat="server" Text="In the table below you will find all of the courses open for registration"></asp:Label>
        <br />
    <asp:Label id="instructions2" runat="server" Text="Please click SELECT of the courses you want to sign up for "></asp:Label>
        <asp:EntityDataSource ID="EntityDataSource1" runat="server" ConnectionString="name=finalModelContainer" DefaultContainerName="finalModelContainer" EnableFlattening="False" EntitySetName="Classes1" Select="it.[CRN], it.[Name]"></asp:EntityDataSource>
        <asp:GridView ID="GridView1" runat="server" DataSourceID="EntityDataSource1" OnSelectedIndexChanged="GridView1_SelectedIndexChanged">
            <Columns>
                <asp:CommandField ShowSelectButton="True" />
            </Columns>
        </asp:GridView>
        <asp:Button ID="Main" runat="server" Text="Return To Main" OnClick="Main_Click"  />
    </form>
</body>
</html>
