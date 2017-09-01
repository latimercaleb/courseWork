using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Windows.Forms;

namespace WebApplication1
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            Response.Redirect("Registration.aspx");
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            if (IsValid)
            {
                var uName = TextBox1.Text;
                var pCode = TextBox2.Text;
                SqlConnection linkToDb = new SqlConnection(@"data source=(LocalDB)\MSSQLLocalDB;attachdbfilename=|DataDirectory|\UserDB.mdf;integrated security=True");
                linkToDb.Open();
                SqlCommand LoginAttempt = new SqlCommand("SELECT Id from Users WHERE LoginID = '" + uName + "' AND Password = '" + pCode + "'", linkToDb);
                SqlDataReader reader = LoginAttempt.ExecuteReader();
                if (reader.HasRows)
                {
                    var login = Server.HtmlEncode(TextBox1.Text);
                    var password = Server.HtmlEncode(TextBox2.Text);
                    System.Diagnostics.Debug.WriteLine("Login Successful");
                    Session.Add(login, password);
                    Response.Redirect("Main.aspx", false);
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("Login Unsuccessful");
                    MessageBox.Show("Please enter a valid user ID and pass");
                }
                
            }
        }
    }
}