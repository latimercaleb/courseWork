using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Windows.Forms;

namespace WebApplication1
{
    public partial class Main : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session.Count != 0)
            {
                MessageBox.Show("Login sucessful!");
                Button1.Visible = true;
                Button2.Visible = false;
                foreach (string session in Session.Keys)
                    Label1.Text = "Welcome " + session +  "<br/> " + "Your session ID is " + Session[session];
            } 
            else
            {
                Button1.Visible = false;
                Button2.Visible = true;
                Label1.Text = "You are not logged in!";
            }
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            Session.Abandon();
            Session.Clear();
            MessageBox.Show("Logout successful!");
            Response.Redirect("Main.aspx");
        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            Response.Redirect("Login.aspx");
        }
    }
}