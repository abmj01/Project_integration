import os.path
from google.oauth2 import service_account
from googleapiclient.discovery import build

data_range = 'Sheet1!A2:I'

FIRST_NAME_COLUMN = 0
LAST_NAME_COLUMN = 1
EMAIL_COLUMN = 2
USERNAME_COLUMN = 3
PASSWORD_COLUMN = 4
CONTACT_COLUMN = 5
WATCH_CODE_COLUMN = 7
FALL_CHECK_COLUMN = 8

USERNAME_COLUMN2 = 1

scope = ['https://www.googleapis.com/auth/spreadsheets']

# a credential JSON file is needed, in order to access Google Sheets.
class DatabaseRetriever:
    def __init__(self, credentials_file, login_spreadsheet_id, contact_person_spreadsheet_id):
        self.credentials_file = credentials_file
        self.login_spreadsheet_id = login_spreadsheet_id
        self.contact_person_spreadsheet_id = contact_person_spreadsheet_id
        self.service = self.authenticate()

    def authenticate(self):
        credentials = service_account.Credentials.from_service_account_file(
            self.credentials_file, scopes=scope)  # creates the credentials from the json file and applies the scope.
        service = build('sheets', 'v4', credentials=credentials)
        return service

    def fetch_contact_person_nr_and_username(self, first_name, last_name):
        # assuming 'A' for name, 'B' for phone number, 'C' for email
        # sheet1 is used as an example name of the sheet you want to get data from.
        result = self.service.spreadsheets().values().get(
            spreadsheetId=self.login_spreadsheet_id,
            range=data_range
        ).execute()  # takes the data from the specified sheet and columns.
        values = result.get('values', [])  # puts the data in rows

        if not values:
            return None  # if the sheet is empty, it returns None

        for row in values:
            if row[FIRST_NAME_COLUMN] == first_name and row[LAST_NAME_COLUMN] == last_name:  # it first checks if the first element of the row is the name
                return "+" + row[CONTACT_COLUMN][2:] + " " + row[USERNAME_COLUMN] if len(row) > 1 else None  # if the row is not empty, it returns the value in the 2nd cell.
        return None

    def fetch_name(self, code):  # very similar to fetch_contact_nr, but it returns the value in the 3rd cell, if it is not empty.
        result = self.service.spreadsheets().values().get(
            spreadsheetId=self.login_spreadsheet_id,
            range=data_range
        ).execute()
        values = result.get('values', [])

        if not values:
            return None
        fullName = ""
        for row in values:
            if row[WATCH_CODE_COLUMN] == code:
                fullName = row[FIRST_NAME_COLUMN] + " " if len(row) > 1 else None
                fullName += row[LAST_NAME_COLUMN] if len(row) > 1 else None
            elif row[WATCH_CODE_COLUMN] is None:
                return None
        return fullName



    def change_fall_cell(self, username):
        result = self.service.spreadsheets().values().get(
            spreadsheetId=self.contact_person_spreadsheet_id,
            range=data_range
        ).execute()
        values = result.get('values', [])

        if not values:
            return

        for idx, row in enumerate(values):
            if row[USERNAME_COLUMN2] == username:
                update_range = f"Sheet1!C{idx + 2}"  # Adjust the column and row based on your sheet
                body = {
                    'values': [[1]]
                }
                self.service.spreadsheets().values().update(
                    spreadsheetId=self.contact_person_spreadsheet_id,
                    range=update_range,
                    valueInputOption="RAW",
                    body=body
                ).execute()
            elif row[USERNAME_COLUMN2] is None:
                return