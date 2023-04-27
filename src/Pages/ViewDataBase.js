import Header from '../Components/Header'
import React, { useRef } from "react";
import { Route, useNavigate, Link, Routes } from "react-router-dom";


export default function ViewDataBase() {

    return (
        <div className="container">
            <div class="topbar">
                <h1>
                    test
                </h1>
            </div>
        
            <div className="bottombar">
                        <div className="sidebar">
                            
                        </div>


                        <div className="main-content">
                            <Header />
                            <h2> View Database Page </h2>
                        </div>
                </div>
            </div>
    )
}
