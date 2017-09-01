using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.Entity;

namespace WebApplication1
{
    public partial class Registration : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (IsPostBack)
            {
                Validate();
            }
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            Validate();
            if (IsValid)
            {
                using (UserDBEntities dbcontext = new UserDBEntities())
                {
                    User user = new User();
                    user.FirstName = TextBox1.Text;
                    user.LastName = TextBox2.Text;
                    user.LoginID = TextBox3.Text;
                    user.Password = TextBox4.Text;
                    dbcontext.Users.Add(user);
                    dbcontext.SaveChanges();
                    messagesEntityDataSource.DataBind();
                    MessageBox.Show("Registration complete");
                }
                Response.Redirect("Login.aspx");
            }
        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            TextBox1.Text = String.Empty;
            TextBox2.Text = String.Empty;
            TextBox3.Text = String.Empty;
            TextBox4.Text = String.Empty;
        }

    }
}