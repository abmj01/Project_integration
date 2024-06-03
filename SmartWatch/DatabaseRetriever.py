import os.path
from google.oauth2 import service_account
from googleapiclient.discovery import build


# a credential JSON file is needed, in order to access Google Sheets.
class DatabaseRetriever:
    def __init__(self, credentials_file, spreadsheet_id):
        self.credentials_file = credentials_file
        self.spreadsheet_id = spreadsheet_id
        self.service = self.authenticate()

    def authenticate(self):
        scope = [
            'https://www.googleapis.com/auth/spreadsheets.readonly']  # defines the required scopes for accessing Google Sheets in read-only mode.
        credentials = service_account.Credentials.from_service_account_file(
            self.credentials_file, scopes=scope)  # creates the credentials from the json file and applies the scope.
        service = build('sheets', 'v4', credentials=credentials)
        return service

    def fetch_contact_person_nr(self, name):
        data_range = 'Sheet1!A2:C'
        # assuming 'A' for name, 'B' for phone number, 'C' for email
        # sheet1 is used as an example name of the sheet you want to get data from.
        result = self.service.spreadsheets().values().get(
            spreadsheetId=self.spreadsheet_id,
            range=data_range
        ).execute()  # takes the data from the specified sheet and columns.
        values = result.get('values', [])  # puts the data in rows

        if not values:
            return None  # if the sheet is empty, it returns None

        for row in values:
            if row[0] == name:  # it first checks if the first element of the row is the name.
                return row[1] if len(
                    row) > 1 else None  # if the row is not empty, it returns the value in the 2nd cell.
        return None

    def fetch_contact_person_email(self, name):  # very similar to fetch_contact_nr, but it returns the value in the 3rd cell, if it is not empty.
        data_range = 'Sheet1!A2:C'

        result = self.service.spreadsheets().values().get(
            spreadsheetId=self.spreadsheet_id,
            range=data_range
        ).execute()
        values = result.get('values', [])

        if not values:
            return None

        for row in values:
            if row[0] == name:
                return row[2] if len(row) > 1 else None
        return None


# Example usage
if __name__ == "__main__":  # this is an example on how to use the class.
    credentialsFile = 'smartguard-db-2d7a3c1c6e81.json' # example of file path
    spreadsheetId = '1SkEwv4F9QjGoJyc82fBE0WMixxoqFOWexwBtG3i0Ppc' # example. the ID can be taken from the link to the sheet, ex: https://docs.google.com/spreadsheets/d/<ID>/edit#gid=0

    api = DatabaseRetriever(credentialsFile, spreadsheetId)

    nameToLookup = 'Mathew'
    phoneNumber = api.fetch_contact_person_nr(nameToLookup)
    email = api.fetch_contact_person_email(nameToLookup)

    print(f'Phone number for {nameToLookup}: {phoneNumber}')
    print(f'Email for {nameToLookup}: {email}')
