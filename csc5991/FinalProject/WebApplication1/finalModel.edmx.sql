
-- --------------------------------------------------
-- Entity Designer DDL Script for SQL Server 2005, 2008, 2012 and Azure
-- --------------------------------------------------
-- Date Created: 08/02/2017 22:50:49
-- Generated from EDMX file: C:\Users\otherUser\Desktop\WebApplication1\WebApplication1\finalModel.edmx
-- --------------------------------------------------

SET QUOTED_IDENTIFIER OFF;
GO
USE [userAndClassPJT];
GO
IF SCHEMA_ID(N'dbo') IS NULL EXECUTE(N'CREATE SCHEMA [dbo]');
GO

-- --------------------------------------------------
-- Dropping existing FOREIGN KEY constraints
-- --------------------------------------------------

IF OBJECT_ID(N'[dbo].[FK_ClassesUser_Class]', 'F') IS NOT NULL
    ALTER TABLE [dbo].[ClassesUser] DROP CONSTRAINT [FK_ClassesUser_Class];
GO
IF OBJECT_ID(N'[dbo].[FK_ClassesUser_User]', 'F') IS NOT NULL
    ALTER TABLE [dbo].[ClassesUser] DROP CONSTRAINT [FK_ClassesUser_User];
GO

-- --------------------------------------------------
-- Dropping existing tables
-- --------------------------------------------------

IF OBJECT_ID(N'[dbo].[Users]', 'U') IS NOT NULL
    DROP TABLE [dbo].[Users];
GO
IF OBJECT_ID(N'[dbo].[Classes1]', 'U') IS NOT NULL
    DROP TABLE [dbo].[Classes1];
GO
IF OBJECT_ID(N'[dbo].[ClassesUser]', 'U') IS NOT NULL
    DROP TABLE [dbo].[ClassesUser];
GO

-- --------------------------------------------------
-- Creating all tables
-- --------------------------------------------------

-- Creating table 'Users'
CREATE TABLE [dbo].[Users] (
    [Id] int IDENTITY(1,1) NOT NULL,
    [FirstName] nvarchar(max)  NOT NULL,
    [LastName] nvarchar(max)  NOT NULL,
    [LoginID] nvarchar(max)  NOT NULL,
    [Password] nvarchar(max)  NOT NULL
);
GO

-- Creating table 'Classes1'
CREATE TABLE [dbo].[Classes1] (
    [CourseID] int IDENTITY(1,1) NOT NULL,
    [CRN] nvarchar(max)  NOT NULL,
    [Name] nvarchar(max)  NOT NULL
);
GO

-- Creating table 'ClassesUser'
CREATE TABLE [dbo].[ClassesUser] (
    [Class_CourseID] int  NOT NULL,
    [Users_Id] int  NOT NULL
);
GO

-- --------------------------------------------------
-- Creating all PRIMARY KEY constraints
-- --------------------------------------------------

-- Creating primary key on [Id] in table 'Users'
ALTER TABLE [dbo].[Users]
ADD CONSTRAINT [PK_Users]
    PRIMARY KEY CLUSTERED ([Id] ASC);
GO

-- Creating primary key on [CourseID] in table 'Classes1'
ALTER TABLE [dbo].[Classes1]
ADD CONSTRAINT [PK_Classes1]
    PRIMARY KEY CLUSTERED ([CourseID] ASC);
GO

-- Creating primary key on [Class_CourseID], [Users_Id] in table 'ClassesUser'
ALTER TABLE [dbo].[ClassesUser]
ADD CONSTRAINT [PK_ClassesUser]
    PRIMARY KEY CLUSTERED ([Class_CourseID], [Users_Id] ASC);
GO

-- --------------------------------------------------
-- Creating all FOREIGN KEY constraints
-- --------------------------------------------------

-- Creating foreign key on [Class_CourseID] in table 'ClassesUser'
ALTER TABLE [dbo].[ClassesUser]
ADD CONSTRAINT [FK_ClassesUser_Class]
    FOREIGN KEY ([Class_CourseID])
    REFERENCES [dbo].[Classes1]
        ([CourseID])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating foreign key on [Users_Id] in table 'ClassesUser'
ALTER TABLE [dbo].[ClassesUser]
ADD CONSTRAINT [FK_ClassesUser_User]
    FOREIGN KEY ([Users_Id])
    REFERENCES [dbo].[Users]
        ([Id])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_ClassesUser_User'
CREATE INDEX [IX_FK_ClassesUser_User]
ON [dbo].[ClassesUser]
    ([Users_Id]);
GO

-- --------------------------------------------------
-- Script has ended
-- --------------------------------------------------