import "./Home.css"
import { useLayoutEffect, React, useState } from 'react';
import ViewDataBase from './ViewDataBase';
import { Route, useNavigate, Link, Routes } from "react-router-dom";
import { Button } from '../Components/Button';



export default function Home() {
    const [button, setButton] = useState(true);
    const navigate = useNavigate();
    const redirectToViewDataBase = () => {
        navigate("/ViewDataBase");
    }

    
    
    return (
        <div className="container">
            <div className="sidebar">
                
            </div>


            <div className="main-content">
                <Link to='/ViewDataBase' className='ViewDataBase'>
                    {button && <Button buttonStyle='btn--primary'> View Data Base
                    </Button>}
                </Link>
                
                <Routes>
                    <Route path="/ViewDataBase" element={<ViewDataBase />} />
                </Routes>
            </div>
        </div>
    )
}