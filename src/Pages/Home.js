import Header from '../Components/Header'
import { useLayoutEffect, React } from 'react';
import ViewDataBase from './ViewDataBase';
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import CreateDataBase from './CreateDataBase';
import "./Home.css";



export default function Home() {
    const navigate = useNavigate();
    const redirectToCreateDataBase = () => {
        navigate("/CreateDataBase");
    };
    const redirectToViewDataBase = () => {
        navigate("/ViewDataBase");
    }
    
    useLayoutEffect(() => {
        document.body.style.backgroundColor = "#10042C"
   });
    return (
        <>
        
            <Header />
            <h2 style={{color: "white"}}> Home Page </h2>
            <hr />
            <button
                onClick={redirectToCreateDataBase}
                style={{ backgroundColor: "#8A5AA4", color: "white", height: '60px', width: '100px' }}
                > Create Database 
            </button>
            <Routes>
                <Route path="/CreateDataBase" element={<CreateDataBase />} />
            </Routes>
            <button
                onClick={redirectToViewDataBase}
                style={{ backgroundColor: "#8A5AA4", color: "white", height: '60px', width: '100px' }}
                > View Database 
            </button>
            <Routes>
                <Route path="/ViewDataBase" element={<ViewDataBase />} />
            </Routes>
            
        </>
        
    )
}
