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
    public partial class Main : System.Web.UI.Page
    {
        SqlConnection databaseConnection = new SqlConnection(@"data source=(LocalDB)\MSSQLLocalDB;attachdbfilename=C:\Users\otherUser\Desktop\WebApplication1\WebApplication1\userAndClassPJT.mdf;integrated security=True");
        int UID;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session.Count != 0)
            {
                Logout.Visible = true;
                Login.Visible = false;
                foreach (string session in Session.Keys)
                    Welcome.Text = "Welcome " + session + ". Please find your schedule below: ";

                databaseConnection.Open();
                SqlCommand Id = new SqlCommand("SELECT Id from Users WHERE LoginID = '" + (string)(Session.Keys[0]) + "'", databaseConnection);
                SqlDataReader readID = Id.ExecuteReader();
                if (readID.Read())
                {
                    UID = int.Parse(readID[0].ToString());
                }
                databaseConnection.Close();
                databaseConnection.Open();
                SqlCommand getClasses = new SqlCommand("SELECT CRN,Name FROM Classes1 AS A INNER JOIN ClassesUser AS B ON A.CourseID = B.Class_CourseID INNER JOIN Users AS C ON B.Users_Id = C.Id WHERE C.Id ='" + UID + "'", databaseConnection);
                SqlDataReader CourseReader = getClasses.ExecuteReader();
                UserData.DataSource = CourseReader;
                UserData.DataBind();
                databaseConnection.Close();

            ClassRegisterPrompt.Text = "To register for more classes please follow the link ";
            } 
            else
            {
                Logout.Visible = false;
                Login.Visible = true;
                ClassRegisterPrompt.Visible = false;
                Registration.Visible = false;
                Welcome.Text = "You are not logged in! Please Login to continue";
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

        protected void Registration_Click(object sender, EventArgs e)
        {
            Response.Redirect("ClassSelect.aspx");
        }

        protected void UserData_SelectedIndexChanged(object sender, EventArgs e)
        {
            SqlConnection linkToDb = new SqlConnection(@"data source=(LocalDB)\MSSQLLocalDB;attachdbfilename=C:\Users\otherUser\Desktop\WebApplication1\WebApplication1\userAndClassPJT.mdf;integrated security=True");
            GridViewRow clickedRow = UserData.SelectedRow;

            linkToDb.Open();
            var courseReference = clickedRow.Cells[1].Text;
            var courseName = clickedRow.Cells[2].Text;
            SqlCommand classToDelete = new SqlCommand($"SELECT CourseID FROM Classes1 WHERE Classes1.CRN = '" + courseReference+"' AND Classes1.Name = '" + courseName+"'",linkToDb);
            Object classID = classToDelete.ExecuteScalar();

            SqlCommand deleteClassForUser = new SqlCommand($"DELETE FROM ClassesUser WHERE ClassesUser.Class_CourseID = ${classID} AND ClassesUser.Users_Id = ${UID}", linkToDb);
            SqlDataReader CourseReader = deleteClassForUser.ExecuteReader();
            MessageBox.Show($"You have dropped for {courseReference}");
            linkToDb.Close();
            Response.Redirect("Main.aspx");
        }
    }
}