import React, { useEffect, useState } from "react";
import fetchJsonp from "fetch-jsonp";
const Header = () => {
  const [phValue, setPhValue] = useState();
  /** 
  useEffect(() => {
    // Function to fetch pH value
    const fetchPH = async () => {
      try {
        // Make the API call
        const response = await fetch("/ph"); // Replace '/ph' with your actual API endpoint
        const data = await response.json();

        // Update the state with the pH value
        setPhValue(data.ph); // Assuming the API response has a property named 'ph'
      } catch (error) {
        console.error("Error fetching pH:", error);
      }
    };

    // Call the fetch function
    fetchPH();
  }, []); **/
  /** 
  useEffect(() => {
    // Function to fetch pH value
    const fetchPH = async () => {
      try {
        // Make the API call
        const response = await fetch("/ph"); // Replace '/ph' with your actual API endpoint

        // Check if the response was successful
        if (!response.ok) {
          // If the response status is not OK, throw an error with the status
          throw new Error(`HTTP error! Status: ${response.status}`);
        }

        // Try parsing the response as JSON
        try {
          const data = await response.json();
          // Assuming the API response has a property named 'ph'
          setPhValue(data.ph);
        } catch (jsonError) {
          // If JSON parsing fails, log the error and throw an error
          console.error("Error parsing JSON:", jsonError);
          throw new Error("Response not in JSON format");
        }
      } catch (error) {
        // Log any errors that occur during the fetch or JSON parsing
        console.error("Error fetching pH:", error);
      }
    };

    // Call the fetch function
    fetchPH();
  }, []);**/
  /** 
  useEffect(() => {
    // Define the JSONP endpoint
    const jsonpEndpoint = "http://172.28.96.149/tds";

    // Make the JSONP request using the fetch-jsonp library
    fetchJsonp(jsonpEndpoint)
      .then((response) => response.json())
      .then((data) => {
        // Set the pH value directly as 'data'
        setPhValue(data);
      })
      .catch((error) => {
        console.error("Error fetching pH:", error);
      });
  }, []); **/
  const [error, setError] = useState();

  useEffect(() => {
    // Define the JSONP endpoint
    const jsonpEndpoint = "http://172.28.96.149/tds";

    // Make the JSONP request using the fetch-jsonp library
    fetchJsonp(jsonpEndpoint, {
      timeout: 5000, // Timeout after 5000 ms
    })
      .then((response) => response.json())
      .then((data) => {
        // Set the pH value directly as 'data'
        setPhValue(data);
      })
      .catch((error) => {
        console.error("Error fetching pH:", error);
        setError(
          "Failed to fetch data. Please check if the server is running and accessible."
        );
      });
  }, []);

  // Call the fetch function
  console.log(phValue);
  return (
    <div>
      <p>Hello World!</p>
      <p>{phValue}</p>
    </div>
  );
};

export default Header;
