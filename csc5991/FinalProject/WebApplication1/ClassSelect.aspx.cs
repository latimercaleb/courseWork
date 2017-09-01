using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Windows.Forms;
using System.Data.SqlClient;


namespace WebApplication1
{
    public partial class ClassSelect : System.Web.UI.Page
    {
        int UID = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session.Count != 0)
            {
                Logout.Visible = true;
                Login.Visible = false;
                foreach (string session in Session.Keys)
                    Welcome.Text = "Welcome " + session + ". Please find the available classes below: ";
                SqlConnection databaseConnection = new SqlConnection(@"data source=(LocalDB)\MSSQLLocalDB;attachdbfilename=C:\Users\otherUser\Desktop\WebApplication1\WebApplication1\userAndClassPJT.mdf;integrated security=True");
                databaseConnection.Open();
                SqlCommand Id = new SqlCommand("SELECT Id from Users WHERE LoginID = '" + (string)(Session.Keys[0]) + "'", databaseConnection);
                SqlDataReader readID = Id.ExecuteReader();
                if (readID.Read())
                {
                    UID = int.Parse(readID[0].ToString());
                }
                databaseConnection.Close();
            }
            else
            {
                Logout.Visible = false;
                Login.Visible = true;
                instructions.Visible = false;
                instructions2.Visible = false;
                GridView1.Visible = false;
                Welcome.Text = "You are not logged in!";
            }
        }

        protected void Logout_Click(object sender, EventArgs e)
        {
            Session.Abandon();
            Session.Clear();
            MessageBox.Show("Logout successful!");
            Response.Redirect("Main.aspx");
        }

        protected void Login_Click(object sender, EventArgs e)
        {
            Response.Redirect("Login.aspx");
        }

        protected void GridView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            SqlConnection linkToDb = new SqlConnection(@"data source=(LocalDB)\MSSQLLocalDB;attachdbfilename=C:\Users\otherUser\Desktop\WebApplication1\WebApplication1\userAndClassPJT.mdf;integrated security=True");
            GridViewRow clickedRow = GridView1.SelectedRow;

            linkToDb.Open();
            var courseReference = clickedRow.Cells[1].Text;
            var courseName = clickedRow.Cells[2].Text;
            SqlCommand addClassToUser = new SqlCommand("SELECT CourseID FROM Classes1 WHERE CRN = '" + courseReference +"'", linkToDb);
            Object classObject = addClassToUser.ExecuteScalar();
            
            SqlCommand completeRegistration = new SqlCommand("INSERT INTO ClassesUser (Class_CourseID, Users_Id) VALUES ('" + classObject + "', '" + UID + "')", linkToDb);
            try
            {
                SqlDataReader courseCheck = completeRegistration.ExecuteReader();
                MessageBox.Show($"You have registered for {courseReference}");
            }
            catch (Exception arg)
            {
                MessageBox.Show("You are already registered");
            }
            linkToDb.Close();
        }

        protected void Main_Click(object sender, EventArgs e)
        {
            Response.Redirect("Main.aspx");
        }
    }
}