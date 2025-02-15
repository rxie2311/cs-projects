# Author: Raymond Xie
# Student No: 251275727
# Description: A TCP server that handles HTTP requests and responds to the client.

import socket
import threading
import os


class Server:
    # Constructor method
    def __init__(self, addr, port, timeout):
        # Required instance variables
        self.addr = addr
        self.port = port
        self.timeout = timeout
        # Variable to keep track of if server is online or offline
        self.online = False
        # Dictionary to store client sessions
        self.sessions = {}

        # Server information
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Binds the server to address and port specified by client
        self.server_socket.bind((self.addr, self.port))
        # Sets the timeout to the value specified by client
        self.server_socket.settimeout(self.timeout)

    # Method to start the server
    def start_server(self):
        # Starting server
        self.server_socket.listen(5)
        # Updates server status to True (online)
        self.online = True

        # Starting up the server
        try:
            # Will loop as long as the server is online
            while self.online:
                try:
                    # Accepts the incoming socket
                    conn, client_addr = self.server_socket.accept()
                    # Uses threading to handle multiple clients
                    threading.Thread(target=self.handle_client, args=(conn, client_addr)).start()
                # If a timeout occurs, notifies the user and stops the server
                except socket.timeout:
                    print(f"Timeout: Server timed out due to inactivity.")
                    self.stop_server()
                    break
        # Catches all exceptions and stops the server if an exception occurs
        except Exception as e:
            print(f"Exception: An exception ({e}) occurred while starting the server.")
            self.stop_server()

    # Extra method added to handle client for threading
    def handle_client(self, conn, client_addr):
        try:
            # Sets the timeout value for the client socket
            conn.settimeout(self.timeout)
            # Calls on handle request to handle the request from conn
            self.handle_request(conn)
        # If a timeout occurs, notifies the user and stops the server
        except socket.timeout:
            print(f"Timeout: Client socket timed out due to inactivity.")
            conn.close()
        # Catches all exceptions and stops the server if an exception occurs
        except Exception as e:
            print(f"Exception: An exception ({e}) occurred while handling the client")
            conn.close()

    # Method to stop the server
    def stop_server(self):
        # Updates server status to False (offline)
        self.online = False
        # Closes the server when called upon
        self.server_socket.close()
        # Print message to update user on status of the server
        print(f"Stopped Server: Server has gone offline.")

    # Method to split up request line, headers and body of the request
    def parse_request(self, request_data):
        # Splitting up the data by \r\n and storing it into an array
        temp_split = request_data.split("\r\n")
        # Store the first split into request line
        request_line = temp_split[0]
        # Creating a new dictionary for all headers and new string for the body
        headers = {}
        body = ""

        # Starting a for loop at index 1, since index 0 is the request line
        for i in temp_split[1:]:
            # Separating header names from header bodies and storing it into a dictionary
            if ":" in i:
                header_name, header_body = i.split(": ")
                # Uses the header name as the key, header body is stored as the value
                headers[header_name] = header_body
            # Once i is a nullspace, that means the headers end
            if i == "":
                # Take the current index that i is in
                curr_index = temp_split.index(i)
                # Store everything past the index i is in +1 into the body variable
                body = body.join(temp_split[curr_index+1:])
                # Breaks out of the for loop after saving the body
                break

        # Returns request line, headers and the body
        return request_line, headers, body

    # Method to handle the request by calling the right helper methods
    def handle_request(self, client_socket):
        try:
            # Decodes the request
            response = client_socket.recv(4096).decode("utf-8")
            # Calls on parse request to fetch the request line, headers and body from the request
            request_line, headers, body = self.parse_request(response)
            # Splits the request line into the method, path and version based on white space
            method, path, version = request_line.split(" ")

            # If the path in the request is empty, automatically defaults to index.html
            if path == "/":
                path = "/index.html"

            # If the method is GET, then calls on handle get request method
            if method == "GET":
                self.handle_get_request(client_socket, path)
            # If the method is POST, then calls on handle post request method
            elif method == "POST":
                self.handle_post_request(client_socket, path, headers, body)
            # If the method is not GET or POST, then calls on handle unsupported method
            else:
                self.handle_unsupported_method(client_socket, method)
        # Catches all exceptions and notifies the user if an exception occurs
        except Exception as e:
            print(f"Exception: An exception ({e}) occurred while handling the request")
        # Closes the client socket at the end
        finally:
            client_socket.close()

    # Method to handle a method that is not POST or GET
    def handle_unsupported_method(self, client_socket, method):
        # Responds to the client socket with 405 Not Allowed
        response = f"HTTP/1.1 405 Method Not Allowed\r\nHost: localhost\r\n\r\nThe method used is not allowed."
        response = response.encode("utf-8")
        client_socket.sendall(response)

    # Method to handle GET methods
    def handle_get_request(self, client_socket, file_path):
        # Gets the client address from the client socket, will be saved as (client address, port)
        client_addr = client_socket.getpeername()
        # Saves the file path as a variable
        path = "assets" + file_path

        try:
            # Opens the file in read if it exists and takes the content in it
            with open(os.path.abspath(path), 'r') as f:
                content = f.read()

            # Gets the client name using the client address (index 0 of the client addr tuple) as the key
            name = self.sessions.get(client_addr[0])
            # If there was no client name specified, defaults the client name as "Client Name"
            if type(name) == type(None):
                name = "Client Name"
            # Replaces {{name}} placeholder with the client name
            content = content.replace("{{name}}", name)

            # Sends a response of 200 OK when name is successfully updated
            response = f"HTTP/1.1 200 OK\r\nHost: localhost\r\n\r\n" + content
            response = response.encode("utf-8")
            client_socket.sendall(response)
        # If the file does not exist
        except FileNotFoundError:
            # Sends a response of 404 Not Found
            response = f"HTTP/1.1 404 Not Found\r\nHost: localhost\r\n\r\nThe file path specified could not be found."
            response = response.encode("utf-8")
            client_socket.sendall(response)

    # Method to handle POST methods
    def handle_post_request(self, client_socket, file_path, headers, body):
        # Taking the client address from the client socket
        client_addr = client_socket.getpeername()
        # Saves the file path
        path = file_path
        # Retrieves the name of the client from the body
        body_split = body.split("=")
        name = body_split[1]
        # Creates a String to store all the headers in
        header = ""

        # Cycle through the dictionary of headers and saves the keys and values into a string
        for i in headers:
            header = header + i + ": " + headers[i] + "\r\n"

        # If the path request is change_name then update the name in sessions dictionary
        if path == "/change_name":
            # Saves the client address as the key and the client name as the value
            self.sessions[client_addr[0]] = name
            # Responds to client with 200 Ok and Name updated
            response = "HTTP/1.1 200 OK\r\n" + header + "\r\n\r\nName updated."
            response = response.encode("utf-8")
            client_socket.sendall(response)
        # If the path request is something else
        else:
            # Responds to client with 404 Not Found and informs the user that the POST request is invalid
            response = f"HTTP/1.1 404 Not Found\r\n" + header + "\r\n\r\nPath is invalid for POST request."
            response = response.encode("utf-8")
            client_socket.sendall(response)
