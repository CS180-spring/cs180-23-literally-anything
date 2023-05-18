import React, { useState } from 'react';
import { Button } from './Button';
import axios from 'axios';

const TextBoxColl = () => {
  const [isOpen, setIsOpen] = useState(false);
  const [userInput, setUserInput] = useState('');
  
  const handleButtonClick = () => {
    setIsOpen(true);
    
  };

  const handleInputChange = (event) => {
    setUserInput(event.target.value);
  };

  const handleFormSubmit = (event) => {
    event.preventDefault();
    console.log('User input:', userInput);
    setIsOpen(false);
    process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;
    
    axios.post('https://54.177.181.151:4000/createCollection', {
      collectionName: userInput
    })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });
  };

  return (
    <div>

    <div className="button">
      {Button && <Button buttonStyle='btn--outline' buttonSize='btn--large' onClick={handleButtonClick}> Create Collection
      </Button>}
      {isOpen && (
        <form onSubmit={handleFormSubmit}>
          <input type="text" value={userInput} onChange={handleInputChange} />
          <Button buttonStyle = 'btn--outline' buttonSize='btn--small'  type="submit" >
            Submit New Collection
          </Button>
        </form>
      )}
    </div>

      {/* <button onClick={handleButtonClick}>Open Text Input</button> */}
      {/* {isOpen && (
        <form onSubmit={handleFormSubmit}>
          <input type="text" value={userInput} onChange={handleInputChange} />
          <button type="submit">Submit</button>
        </form>
      )} */}
    </div>
  );
};

export default TextBoxColl;