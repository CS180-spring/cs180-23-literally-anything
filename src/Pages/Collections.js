import './Collections.css';
import React from 'react';
import TextBox from '../Components/TextBox';

function Collection() {

    return(
        <div className="Collections">
            <div className="container">
                <div className="left-collumn">
                    <h1>ReactDB+</h1>
                        <TextBox/>
                </div>
                <div className="main_content">
                    
                </div>
                
            </div>
        </div>
    )

}

export default Collection;